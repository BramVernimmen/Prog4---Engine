#pragma once
#include "Event.h"

namespace dae
{
	class AudioLoad final : public Event {};
	class AudioPlay final : public Event {};
	class AudioLoadTrack final : public Event {};
	class AudioPlayTrack final : public Event {};
	class SceneLoaded final : public Event {};
	class ObjectOverlapping final : public Event {};
}