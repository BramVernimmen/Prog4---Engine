#include "EnemyRunningState.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "RigidBody.h"
#include "EnemyComponent.h"
#include "GameTime.h"

dae::EnemyRunningState::EnemyRunningState(GameObject* pEnemy)
{
	m_pEnemy = pEnemy;
	m_pRenderComp = pEnemy->GetComponent<RenderComponent>();
}

void dae::EnemyRunningState::OnEnter()
{
	if (!m_pRigidBody)
		m_pRigidBody = m_pEnemy->GetComponent<RigidBody>();

	m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pRunningTexture);
}

void dae::EnemyRunningState::Update()
{
	if (!m_pRigidBody->IsGrounded() && m_pRigidBody->GetVelocity().y < 0.0f)
	{
		// change to falling
		m_pEnemy->GetComponent<EnemyComponent>()->SetEnemyFalling();
	}

	if (m_WalkDuration == 0.0f)
	{
		glm::vec2 newVelocity{0.0f, 0.0f};
		int randomNumber{ rand() % 100 };
	
		if (randomNumber < 30)
		{
			newVelocity.x = -1.0f * m_MovementSpeed;
		}
		else if (randomNumber > 50)
		{
			newVelocity.x = m_MovementSpeed;
		}
	
		if (newVelocity.x > 0)
		{
			m_pRenderComp->SetFlipTexutures(false);
		}
		else if (newVelocity.x < 0)
		{
			m_pRenderComp->SetFlipTexutures(true);
		}
	
		m_CachedXVelocity = newVelocity.x;
	
		if (randomNumber < 10)
		{
			newVelocity.y = m_JumpStrength;
			m_pEnemy->GetComponent<EnemyComponent>()->SetEnemyJumping();
		}
	
		m_pRigidBody->SetVelocity(newVelocity);
		m_WalkDuration += GameTime::GetInstance().GetDeltaTime();
	}
	else
	{
		m_WalkDuration += GameTime::GetInstance().GetDeltaTime();
	
		m_pRigidBody->SetVelocity({m_CachedXVelocity ,m_pRigidBody->GetVelocity().y});
		m_pRigidBody->SetGrounded(false);
	
		if (m_WalkDuration >= m_MaxWalkDuration)
			m_WalkDuration = 0.0f;
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
