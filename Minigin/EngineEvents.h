#pragma once
#include "Event.h"

namespace dae
{
	class AudioLoad final : public Event {};
	class AudioPlay final : public Event {};
	class SceneLoaded final : public Event {};
}