#pragma once
#include <memory>
#include "NullSoundSystem.h"

namespace dae
{

	class ServiceLocator final
	{
	public:
		ServiceLocator() = delete;
		~ServiceLocator() = default;

		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) = delete;


		static SoundSystem& GetSoundSystem();
		static void SetSoundSystem(SoundSystem* ss);


	private:
		static std::unique_ptr<SoundSystem> m_pSSInstance;
	};
}

