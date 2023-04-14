#pragma once
#include "Event.h"

namespace dae
{
	class PlayerDamaged : public Event {};
	class PlayerDied : public Event {};
	class GainedScore : public Event {};
}