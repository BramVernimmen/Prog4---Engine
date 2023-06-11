#include "EnemySpawnComponent.h"

dae::EnemySpawnComponent::EnemySpawnComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::EnemySpawnComponent::SetSpawnPosition(float x, float y)
{
	m_SpawnPosition.x = x;
	m_SpawnPosition.y = y;
}
