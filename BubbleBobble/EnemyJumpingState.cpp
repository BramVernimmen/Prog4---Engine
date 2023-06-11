#include "EnemyJumpingState.h"
#include "RigidBody.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GridComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include "BoxCollision.h"

dae::EnemyJumpingState::EnemyJumpingState(GameObject* pEnemy)
{
	m_pEnemy = pEnemy;
	m_pRigidBody = pEnemy->GetComponent<RigidBody>();
	m_pBoxCollision = pEnemy->GetComponent<BoxCollision>();

	auto pGrids{ SceneManager::GetInstance().GetActiveScene()->GetRoot()->GetComponentsInChildren<GridComponent>() };
	auto firstGrid{ pGrids.front() };
	m_TopPosY = firstGrid->GetOwner()->GetComponent<TransformComponent>()->GetLocalPosition().y;
	m_GridPixelSize = firstGrid->GetPixelSize();
	m_BottomPosY = static_cast<float>(firstGrid->GetHeight() * m_GridPixelSize);

	m_MaxBottomPosY = m_BottomPosY + m_GridPixelSize;
	m_MaxTopPosY = m_TopPosY - m_GridPixelSize;

	m_pTransformComp = pEnemy->GetComponent<TransformComponent>();
}

void dae::EnemyJumpingState::OnEnter()
{
	m_pBoxCollision->AddIgnoreLayer(0b10);
}

void dae::EnemyJumpingState::Update()
{
	auto& localPos{ m_pTransformComp->GetLocalPosition() };
	if (localPos.y < m_MaxTopPosY)
	{
		m_pTransformComp->SetLocalPosition(localPos.x, m_MaxBottomPosY);
	}

	if (m_pRigidBody->GetVelocity().y <= 0.0f)
	{
		// switch state to falling
		m_pEnemy->GetComponent<EnemyComponent>()->SetEnemyFalling();
	}
}

void dae::EnemyJumpingState::OnExit()
{
	m_pBoxCollision->RemoveIgnoreLayer(0b10);
}
