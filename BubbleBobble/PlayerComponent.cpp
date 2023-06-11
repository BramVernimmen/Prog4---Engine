#include "PlayerComponent.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerManager.h"
#include "BoxCollision.h"
#include "Texture2D.h"


dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pCurrentState = m_pPlayerRunningState.get();
	m_pCurrentState->OnEnter();
}

void dae::PlayerComponent::Update()
{
	// handle states here
	m_pCurrentState->Update();
}

void dae::PlayerComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(ObjectOverlapping)) // handle things here
	{
		if (payload.type() == typeid(GameObject*))
		{
			if (std::any_cast<GameObject*>(payload)->GetComponent<PlayerComponent>())
			{
				NotifyObservers(PlayerHit());
				PlayerManager::GetInstance().RespawnPlayer(GetOwner(), m_PlayerId);
				NotifyObservers(ItemPickedUp(), 200);
			}
		}
	}
	if (typeid(currEvent) == typeid(PlayerDied))
	{
		// set to dead state, this is just a temp test
		GetOwner()->GetComponent<RigidBody>()->SetKinematic(true);
		GetOwner()->GetComponent<BoxCollision>()->SetInactive();
	}
}

void dae::PlayerComponent::SetPlayerFalling()
{
	m_pCurrentState = m_pPlayerFallingState.get();
	m_pCurrentState->OnEnter();
}

void dae::PlayerComponent::SetPlayerRunning()
{
	m_pCurrentState = m_pPlayerRunningState.get();
	m_pCurrentState->OnEnter();
}

void dae::PlayerComponent::SetPlayerJumping()
{
	m_pCurrentState = m_pPlayerJumpingState.get();
	m_pCurrentState->OnEnter();
}

void dae::PlayerComponent::SetJumpingSoundId(unsigned short id)
{
	m_pPlayerJumpingState->SetJumpSoundId(id);
}

void dae::PlayerComponent::SetMovementSpeed(float newSpeed)
{
	m_pPlayerRunningState->SetMovementSpeed(newSpeed);
}

void dae::PlayerComponent::SetJumpingStrength(float newJump)
{
	m_pPlayerRunningState->SetJumpStrength(newJump);
}

void dae::PlayerComponent::SetIdleTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pPlayerRunningState->SetTexture(newTexture);
}

