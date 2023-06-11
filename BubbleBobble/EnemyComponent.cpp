#include "EnemyComponent.h"

dae::EnemyComponent::EnemyComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pCurrentState = m_pEnemyRunningState.get();
	m_pCurrentState->OnEnter();
}

void dae::EnemyComponent::Update()
{
	m_pCurrentState->Update();
}

void dae::EnemyComponent::SetEnemyFalling()
{
	m_pCurrentState->OnExit();
	m_pCurrentState = m_pEnemyFallingState.get();
	m_pCurrentState->OnEnter();
}

void dae::EnemyComponent::SetEnemyRunning()
{
	m_pCurrentState->OnExit();
	m_pCurrentState = m_pEnemyRunningState.get();
	m_pCurrentState->OnEnter();
}

void dae::EnemyComponent::SetEnemyJumping()
{
	m_pCurrentState->OnExit();
	m_pCurrentState = m_pEnemyJumpingState.get();
	m_pCurrentState->OnEnter();
}

void dae::EnemyComponent::SetEnemyBubble()
{
	m_pCurrentState->OnExit();
	m_pCurrentState = m_pEnemyBubbleState.get();
	m_pCurrentState->OnEnter();
}

void dae::EnemyComponent::SetEnemyDeath()
{
	m_pCurrentState->OnExit();
	m_pCurrentState = m_pEnemyDeathState.get();
	m_pCurrentState->OnEnter();
}


void dae::EnemyComponent::SetMovementSpeed(float newSpeed)
{
	m_pEnemyRunningState->SetMovementSpeed(newSpeed);
}

void dae::EnemyComponent::SetJumpingStrength(float newJump)
{
	m_pEnemyRunningState->SetJumpStrength(newJump);
}

void dae::EnemyComponent::SetIdleTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pEnemyRunningState->SetTexture(newTexture);
}

void dae::EnemyComponent::SetBubbleTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pEnemyBubbleState->SetTexture(newTexture);
}

void dae::EnemyComponent::SetDeathTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pEnemyDeathState->SetTexture(newTexture);
}
