#pragma once
#include "Event.h"
#include "EngineEvents.h"

namespace dae
{
	class PlayerHit final : public Event {};
	class PlayerDied final : public Event {};
	class EnemyKilled final : public Event {};
	class GainedScore final : public Event {};
	class ItemPickedUp final : public Event {};

}