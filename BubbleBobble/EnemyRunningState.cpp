#include "EnemyRunningState.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "RigidBody.h"
#include "EnemyComponent.h"


dae::EnemyRunningState::EnemyRunningState(GameObject* pEnemy)
{
	m_pEnemy = pEnemy;
	m_pRenderComp = pEnemy->GetComponent<RenderComponent>();
	m_pRigidBody = pEnemy->GetComponent<RigidBody>();
}

void dae::EnemyRunningState::OnEnter()
{
	m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pRunningTexture);
}

void dae::EnemyRunningState::Update()
{
	// do some movement

	if (!m_pRigidBody->IsGrounded() && m_pRigidBody->GetVelocity().y < 0.0f)
	{
		// change to falling
		m_pEnemy->GetComponent<EnemyComponent>()->SetEnemyFalling();
	}
}

void dae::EnemyRunningState::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pRunningTexture = newTexture;

	if (m_pEnemy->GetComponent<EnemyComponent>()->GetCurrentState() == this)
	{
		// check if we are already active; if so we need to refresh the textureComponent again
		m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pRunningTexture);
	}
}
