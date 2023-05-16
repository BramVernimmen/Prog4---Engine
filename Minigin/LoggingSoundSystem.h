#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{

	class LoggingSoundSystem final : public SoundSystem
	{
	public:
		explicit LoggingSoundSystem(SoundSystem* pSS);
		~LoggingSoundSystem() = default;

		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

		void Play(const unsigned short id) override;
		void Load(const unsigned short id, const std::string& path) override;

	private:
		std::unique_ptr<SoundSystem> m_pSS;

	};
}

