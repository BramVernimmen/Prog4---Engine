#include "PlayerRunningState.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "RigidBody.h"
#include "PlayerComponent.h"

dae::PlayerRunningState::PlayerRunningState(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pRenderComp = pPlayer->GetComponent<RenderComponent>();
	m_pRigidBody = pPlayer->GetComponent<RigidBody>();
}

void dae::PlayerRunningState::OnEnter()
{
	m_pPlayer->GetComponent<TextureComponent>()->SetTexture(m_pRunningTexture);
}

void dae::PlayerRunningState::Update()
{

	if (!m_pRigidBody->IsGrounded() && m_pRigidBody->GetVelocity().y < 0.0f)
	{
		// change to falling
		m_pPlayer->GetComponent<PlayerComponent>()->SetPlayerFalling();
	}
}

void dae::PlayerRunningState::HandleInput(std::any payload)
{
	if (payload.type() == typeid(glm::vec2))
	{
		auto axisValue = std::any_cast<glm::vec2>(payload);

		if (axisValue.y <= 0.0f)
			axisValue.y = 0.0f;
		else
		{
			// change into jumping State
			m_pPlayer->GetComponent<PlayerComponent>()->SetPlayerJumping();
		}

		axisValue.x *= m_MovementSpeed;
		axisValue.y *= m_JumpStrength;

		if (axisValue.x > 0)
		{
			m_pRenderComp->SetFlipTexutures(false);
		}
		else if (axisValue.x < 0)
		{
			m_pRenderComp->SetFlipTexutures(true);
		}

		const auto& currVelocity = m_pRigidBody->GetVelocity();
		m_pRigidBody->SetVelocity({ axisValue.x, currVelocity.y + axisValue.y });
		m_pRigidBody->SetGrounded(false);

	}
}

void dae::PlayerRunningState::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pRunningTexture = newTexture;

	if (m_pPlayer->GetComponent<PlayerComponent>()->GetCurrentState() == this)
	{
		// check if we are already active; if so we need to refresh the textureComponent again
		m_pPlayer->GetComponent<TextureComponent>()->SetTexture(m_pRunningTexture);
	}
}
