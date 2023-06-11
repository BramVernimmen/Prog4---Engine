#pragma once
#include "SoundSystem.h"
#include <memory>


namespace dae
{
	
	class SdlSoundSystem final : public SoundSystem
	{
	public:
		explicit SdlSoundSystem();
		~SdlSoundSystem();

		SdlSoundSystem(const SdlSoundSystem& other) = delete;
		SdlSoundSystem(SdlSoundSystem&& other) = delete;
		SdlSoundSystem& operator=(const SdlSoundSystem& other) = delete;
		SdlSoundSystem& operator=(SdlSoundSystem&& other) = delete;

		void Play(const unsigned short id) override;
		void Load(const unsigned short id, const std::string& path) override;
		void MuteOrUnMute() override;

	private:
		class SdlSoundSystemImpl;
		std::unique_ptr<SdlSoundSystemImpl> m_pImpl;
	};

}
