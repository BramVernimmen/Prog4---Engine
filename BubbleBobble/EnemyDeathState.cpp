#include "EnemyDeathState.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "EnemyComponent.h"
#include "RigidBody.h"
#include "BoxCollision.h"

dae::EnemyDeathState::EnemyDeathState(GameObject* pEnemy)
{
	m_pEnemy = pEnemy;
	m_pRenderComp = pEnemy->GetComponent<RenderComponent>();

}

void dae::EnemyDeathState::OnEnter()
{
	m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pDeathTexture);
	m_pEnemy->GetComponent<RigidBody>()->SetIgnoreGravity(false);
	m_pEnemy->GetComponent<BoxCollision>()->SetInactive();
	m_pEnemy->GetComponent<BoxCollision>()->SetCurrentLayer(0b0);

	// spawn item
}

void dae::EnemyDeathState::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pDeathTexture = newTexture;

	if (m_pEnemy->GetComponent<EnemyComponent>()->GetCurrentState() == this)
	{
		// check if we are already active; if so we need to refresh the textureComponent again
		m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pDeathTexture);
	}
}
