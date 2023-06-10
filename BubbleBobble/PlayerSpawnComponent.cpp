#include "PlayerSpawnComponent.h"

dae::PlayerSpawnComponent::PlayerSpawnComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::PlayerSpawnComponent::SetSpawnPosition(float x, float y)
{
	m_SpawnPosition.x = x;
	m_SpawnPosition.y = y;
}
