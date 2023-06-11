#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(SoundSystem* pSS)
	:m_pSS{std::unique_ptr<SoundSystem>(pSS)}
{
}

void dae::LoggingSoundSystem::Play(const unsigned short id)
{
	m_pSS->Play(id);
	std::cout << "sound played with id: " << id << "\n";
}

void dae::LoggingSoundSystem::Load(const unsigned short id, const std::string& path)
{
	m_pSS->Load(id, path);
	std::cout << "sound with path: " << path << " will be loaded on id: " << id << "\n";

}

void dae::LoggingSoundSystem::PlayTrack(const unsigned short id)
{
	m_pSS->PlayTrack(id);
	std::cout << "track playing with id: " << id << "\n";
}

void dae::LoggingSoundSystem::LoadTrack(const unsigned short id, const std::string& path)
{
	m_pSS->LoadTrack(id, path);
	std::cout << "track with path: " << path << " will be loaded on id: " << id << "\n";
}

void dae::LoggingSoundSystem::MuteOrUnMute()
{
	m_pSS->MuteOrUnMute();
	std::cout << "All Sounds are now Muted/UnMuted" << "\n";
}
