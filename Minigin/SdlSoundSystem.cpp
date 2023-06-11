#include "SdlSoundSystem.h"
#include <SDL_mixer.h>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include "ResourceManager.h"
#include <queue>
#include "EngineEvents.h"
#include <any>
#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>

using namespace dae;

class SdlSoundSystem::SdlSoundSystemImpl
{
	struct AudioEvent
	{
		std::unique_ptr<Event> eventType;
		std::any payload;
	};
	struct LoadStruct
	{
		unsigned short id;
		std::string path;
	};

public:
	SdlSoundSystemImpl()
	{
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
		{
			throw std::runtime_error(std::string("Failed to open audio: ") + Mix_GetError());
		}

		m_AudioHandlerThread = std::jthread(&SdlSoundSystemImpl::HandleQueue, this);
		m_StopToken = m_AudioHandlerThread.get_stop_token();
	}

	~SdlSoundSystemImpl()
	{
		m_AudioHandlerThread.request_stop();
		m_ConditionVariable.notify_all();


		// check if the thread has ended yet, if not, wait for it
		// this wait shouldn't be long as the stop has been requested so it just has to end the function
		if (m_AudioHandlerThread.joinable())
			m_AudioHandlerThread.join();


		for (const auto& currChunk : m_LoadedSounds)
		{
			if (currChunk.second != nullptr)
			{
				Mix_FreeChunk(currChunk.second);
			}
		}
		
		for (const auto& currTrack : m_LoadedTracks)
		{
			if (currTrack.second != nullptr)
			{
				Mix_FreeMusic(currTrack.second);
			}
		}

		Mix_CloseAudio();
		Mix_Quit();
	}

	void Play(const unsigned short id) 
	{
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_EventQueue.push(AudioEvent{ std::make_unique<AudioPlay>(), id });
		}
		m_ConditionVariable.notify_one();
	}

	void HandlePlay(const unsigned short id)
	{
		// play sound
		std::unique_lock<std::mutex> lock(m_Mutex);
		Mix_Chunk* currSound = m_LoadedSounds[id];

		lock.unlock();

		if (currSound != nullptr)
		{
			// play the sound
			Mix_PlayChannel(-1, currSound, 0);
		}
	}

	void PlayTrack(const unsigned short id) 
	{
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_EventQueue.push(AudioEvent{ std::make_unique<AudioPlayTrack>(), id });
		}
		m_ConditionVariable.notify_one();
	}

	void HandlePlayTrack(const unsigned short id)
	{
		// play sound
		std::unique_lock<std::mutex> lock(m_Mutex);
		Mix_Music* currTrack = m_LoadedTracks[id];

		lock.unlock();

		if (currTrack != nullptr)
		{
			// play the sound
			Mix_PlayMusic(currTrack, -1);
		}
	}
	

	void Load(const unsigned short id, const std::string& path)
	{
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_EventQueue.push(AudioEvent{ std::make_unique<AudioLoad>(), LoadStruct{id, path} });
		}
		m_ConditionVariable.notify_one();
	}

	void HandleLoad(const unsigned short id, const std::string& path)
	{
		// load the sound before the lock -> loading the sound takes most of the time
		const auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
		Mix_Chunk* newSound = Mix_LoadWAV(fullPath.c_str());

		Mix_Chunk* soundToFree{nullptr};
		std::unique_lock<std::mutex> lock(m_Mutex);

		if (m_LoadedSounds[id] != nullptr)
		{
			// release the old sound and replace with new
			soundToFree = m_LoadedSounds[id];
		}
		
		m_LoadedSounds[id] = newSound;

		if (m_LoadedSounds[id] == nullptr)
			throw std::runtime_error(std::string("Failed to load sound: ") + SDL_GetError());

		lock.unlock();

		if (soundToFree)
			Mix_FreeChunk(soundToFree);
	}


	void LoadTrack(const unsigned short id, const std::string& path)
	{
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_EventQueue.push(AudioEvent{ std::make_unique<AudioLoadTrack>(), LoadStruct{id, path} });
		}
		m_ConditionVariable.notify_one();
	}

	void HandleLoadTrack(const unsigned short id, const std::string& path)
	{
		// load the sound before the lock -> loading the sound takes most of the time
		const auto fullPath = dae::ResourceManager::GetInstance().GetDataPath() + path;
		Mix_Music* newTrack = Mix_LoadMUS(fullPath.c_str());

		Mix_Music* trackToFree{ nullptr };
		std::unique_lock<std::mutex> lock(m_Mutex);

		if (m_LoadedTracks[id] != nullptr)
		{
			// release the old sound and replace with new
			trackToFree = m_LoadedTracks[id];
		}

		m_LoadedTracks[id] = newTrack;

		if (m_LoadedTracks[id] == nullptr)
			throw std::runtime_error(std::string("Failed to load sound: ") + SDL_GetError());

		lock.unlock();

		if (trackToFree)
			Mix_FreeMusic(trackToFree);
	}


	void HandleQueue()
	{

		// needs the double while, otherwise can get into an infinite loop
		while (!m_StopToken.stop_requested()) 
		{
			std::unique_lock<std::mutex> lock(m_Mutex);

			if (m_EventQueue.empty())
				m_ConditionVariable.wait(lock);


			// just for testing right now
			while (!m_EventQueue.empty() && !m_StopToken.stop_requested())
			{
				// handle all events
				AudioEvent currEvent = std::move(m_EventQueue.front());

				m_EventQueue.pop();

				lock.unlock();

				if (typeid(*currEvent.eventType) == typeid(AudioLoad)) //load audio
				{
					// handle payload
					LoadStruct loadInfo{ std::any_cast<LoadStruct>(currEvent.payload)}; // payload should always be correct

					HandleLoad(loadInfo.id, loadInfo.path);
					
				}
				else if (typeid(*currEvent.eventType) == typeid(AudioPlay)) // play sound
				{
					HandlePlay(std::any_cast<unsigned short>(currEvent.payload));
				}
				else if (typeid(*currEvent.eventType) == typeid(AudioPlayTrack)) // play track
				{
					HandlePlayTrack(std::any_cast<unsigned short>(currEvent.payload));
				}
				else if (typeid(*currEvent.eventType) == typeid(AudioLoadTrack)) // load track
				{
					LoadStruct loadInfo{ std::any_cast<LoadStruct>(currEvent.payload) }; // payload should always be correct
					HandleLoadTrack(loadInfo.id, loadInfo.path);
				}

				lock.lock();
			}
		}
	}

	void MuteOrUnMute()
	{
		m_IsMuted = !m_IsMuted;
		if (m_IsMuted)
		{
			Mix_Volume(-1, 0);
			Mix_VolumeMusic(0);
		}
		else
		{
			Mix_Volume(-1, m_CurrentVolume);
			Mix_VolumeMusic(m_CurrentVolume);
		}
	}

private:

	// we want to link a sound ID to a Mix_Chunk
	// this way we can use sound ID to play a sound
	// but before we can play a sound, we have to load them.
	std::unordered_map<unsigned short, Mix_Chunk*> m_LoadedSounds{};
	std::unordered_map<unsigned short, Mix_Music*> m_LoadedTracks{};

	std::queue<AudioEvent> m_EventQueue{};
	std::jthread m_AudioHandlerThread{};
	std::mutex m_Mutex{};
	std::stop_token m_StopToken{}; // we use this to cache the stop_token from our thread -> no need to constantly ask the thread for it
	std::condition_variable m_ConditionVariable{};

	bool m_IsMuted{ false };

	int m_CurrentVolume{ SDL_MIX_MAXVOLUME };
};



dae::SdlSoundSystem::SdlSoundSystem()
	: m_pImpl{std::make_unique<SdlSoundSystemImpl>()}
{
}

dae::SdlSoundSystem::~SdlSoundSystem() = default;

void dae::SdlSoundSystem::Play(const unsigned short id)
{
	m_pImpl->Play(id);
}

void dae::SdlSoundSystem::Load(const unsigned short id, const std::string& path)
{
	m_pImpl->Load(id, path);
}

void dae::SdlSoundSystem::PlayTrack(const unsigned short id)
{
	m_pImpl->PlayTrack(id);
}

void dae::SdlSoundSystem::LoadTrack(const unsigned short id, const std::string& path)
{
	m_pImpl->LoadTrack(id, path);
}

void dae::SdlSoundSystem::MuteOrUnMute()
{
	m_pImpl->MuteOrUnMute();
}
