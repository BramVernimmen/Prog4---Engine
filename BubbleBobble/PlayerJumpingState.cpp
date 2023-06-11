#include "PlayerJumpingState.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerComponent.h"
#include "BoxCollision.h"
#include <glm/glm.hpp>
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GridComponent.h"
#include "TransformComponent.h"

dae::PlayerJumpingState::PlayerJumpingState(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pRigidBody = pPlayer->GetComponent<RigidBody>();
	m_pBoxCollision = pPlayer->GetComponent<BoxCollision>();
	m_pRenderComp = pPlayer->GetComponent<RenderComponent>();

	auto pGrids{ SceneManager::GetInstance().GetActiveScene()->GetRoot()->GetComponentsInChildren<GridComponent>() };
	auto firstGrid{ pGrids.front() };
	m_TopPosY = firstGrid->GetOwner()->GetComponent<TransformComponent>()->GetLocalPosition().y;
	m_GridPixelSize = firstGrid->GetPixelSize();
	m_BottomPosY = static_cast<float>(firstGrid->GetHeight() * m_GridPixelSize);

	m_MaxBottomPosY = m_BottomPosY + m_GridPixelSize;
	m_MaxTopPosY = m_TopPosY - m_GridPixelSize;

	m_pTransformComp = pPlayer->GetComponent<TransformComponent>();

}

void dae::PlayerJumpingState::OnEnter()
{
	ServiceLocator::GetSoundSystem().Play(m_JumpSoundId);
	m_pBoxCollision->AddIgnoreLayer(0b10);
}

void dae::PlayerJumpingState::Update()
{
	auto& localPos{ m_pTransformComp->GetLocalPosition() };
	if (localPos.y < m_MaxTopPosY)
	{
		m_pTransformComp->SetLocalPosition(localPos.x, m_MaxBottomPosY);
	}

	if (m_pRigidBody->GetVelocity().y <= 0.0f)
	{
		// switch state to falling
		m_pPlayer->GetComponent<PlayerComponent>()->SetPlayerFalling();
	}
}

void dae::PlayerJumpingState::OnExit()
{
	m_pBoxCollision->RemoveIgnoreLayer(0b10);
}

void dae::PlayerJumpingState::HandleInput(std::any payload)
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
