#pragma once
#include <string>
// the interface of our SoundSystem
namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const unsigned short id) = 0;
		virtual void Load(const unsigned short id, const std::string& path) = 0;
		virtual void MuteOrUnMute() = 0;
	};
}