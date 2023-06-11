#include "PlayerFallingState.h"
#include "RenderComponent.h"
#include "RigidBody.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include <iostream>

dae::PlayerFallingState::PlayerFallingState(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pRenderComp = pPlayer->GetComponent<RenderComponent>();
	m_pRigidBody = pPlayer->GetComponent<RigidBody>();
}

void dae::PlayerFallingState::Update()
{
	if (m_pRigidBody->IsGrounded())
	{
		// change to running
		m_pPlayer->GetComponent<PlayerComponent>()->SetPlayerRunning();
	}
}

void dae::PlayerFallingState::HandleInput(std::any payload)
{
	if (payload.type() == typeid(glm::vec2))
	{
		auto axisValue = std::any_cast<glm::vec2>(payload);

		if (axisValue.x > 0)
		{
			m_pRenderComp->SetFlipTexutures(false);
		}
		else if (axisValue.x < 0)
		{
			m_pRenderComp->SetFlipTexutures(true);
		}

	}
}
