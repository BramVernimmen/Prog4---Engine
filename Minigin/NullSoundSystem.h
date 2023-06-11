#pragma once
#include "SoundSystem.h"

namespace dae
{

	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() = default;

		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;

		void Play(const unsigned short ) override { /*do nothing*/ }
		void Load(const unsigned short , const std::string& ) override {/*do nothing*/ }
		void MuteOrUnMute() override {/*do nothing*/ }
	};

}
