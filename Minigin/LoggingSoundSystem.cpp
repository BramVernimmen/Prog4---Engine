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