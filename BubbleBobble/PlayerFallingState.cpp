#include "PlayerFallingState.h"
#include "RenderComponent.h"
#include "RigidBody.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GridComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>

dae::PlayerFallingState::PlayerFallingState(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pRenderComp = pPlayer->GetComponent<RenderComponent>();
	m_pRigidBody = pPlayer->GetComponent<RigidBody>();

	auto pGrids{ SceneManager::GetInstance().GetActiveScene()->GetRoot()->GetComponentsInChildren<GridComponent>() };
	auto firstGrid{ pGrids.front() };
	m_TopPosY = firstGrid->GetOwner()->GetComponent<TransformComponent>()->GetLocalPosition().y;
	m_GridPixelSize = firstGrid->GetPixelSize();
	m_BottomPosY = static_cast<float>(firstGrid->GetHeight() * m_GridPixelSize);

	m_MaxBottomPosY = m_BottomPosY + m_GridPixelSize;
	m_MaxTopPosY = m_TopPosY - m_GridPixelSize;

	m_pTransformComp = pPlayer->GetComponent<TransformComponent>();

}

void dae::PlayerFallingState::Update()
{
	auto& localPos{ m_pTransformComp->GetLocalPosition() };
	if (localPos.y > m_MaxBottomPosY)
	{
		m_pTransformComp->SetLocalPosition(localPos.x, m_MaxTopPosY);
	}

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
