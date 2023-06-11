#include "EnemyFallingState.h"
#include "RigidBody.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GridComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>

dae::EnemyFallingState::EnemyFallingState(GameObject* pEnemy)
{
	m_pEnemy = pEnemy;
	m_pRigidBody = pEnemy->GetComponent<RigidBody>();

	auto pGrids{ SceneManager::GetInstance().GetActiveScene()->GetRoot()->GetComponentsInChildren<GridComponent>() };
	auto firstGrid{ pGrids.front() };
	m_TopPosY = firstGrid->GetOwner()->GetComponent<TransformComponent>()->GetLocalPosition().y;
	m_GridPixelSize = firstGrid->GetPixelSize();
	m_BottomPosY = static_cast<float>(firstGrid->GetHeight() * m_GridPixelSize);

	m_MaxBottomPosY = m_BottomPosY + m_GridPixelSize;
	m_MaxTopPosY = m_TopPosY - m_GridPixelSize;

	m_pTransformComp = pEnemy->GetComponent<TransformComponent>();
}

void dae::EnemyFallingState::Update()
{
	auto& localPos{ m_pTransformComp->GetLocalPosition() };
	if (localPos.y > m_MaxBottomPosY)
	{
		m_pTransformComp->SetLocalPosition(localPos.x, m_MaxTopPosY);
	}

	if (m_pRigidBody->IsGrounded())
	{
		// change to running
		m_pEnemy->GetComponent<EnemyComponent>()->SetEnemyRunning();
	}
}
