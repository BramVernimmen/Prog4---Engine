#include "ServiceLocator.h"


std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_pSSInstance{ std::make_unique<dae::NullSoundSystem>() };



dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_pSSInstance;
}

void dae::ServiceLocator::SetSoundSystem(SoundSystem* ss)
{
	if (ss == nullptr)
	{
		m_pSSInstance = std::make_unique<dae::NullSoundSystem>();
	}
	else
	{
		m_pSSInstance = std::unique_ptr<SoundSystem>(ss);
	}
}
