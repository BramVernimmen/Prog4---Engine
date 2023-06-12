#include "EnemyBubbleState.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "EnemyComponent.h"
#include "RigidBody.h"
#include "BoxCollision.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GridComponent.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include "GameTime.h"

dae::EnemyBubbleState::EnemyBubbleState(GameObject* pEnemy)
{
	m_pEnemy = pEnemy;
	m_pRenderComp = pEnemy->GetComponent<RenderComponent>();

	auto pGrids{ SceneManager::GetInstance().GetActiveScene()->GetRoot()->GetComponentsInChildren<GridComponent>() };
	auto firstGrid{ pGrids.front() };
	m_TopPosY = firstGrid->GetOwner()->GetComponent<TransformComponent>()->GetLocalPosition().y;
	m_GridPixelSize = firstGrid->GetPixelSize();

	m_MaxTopPosY = m_TopPosY + m_GridPixelSize;
	m_pTransformComp = pEnemy->GetComponent<TransformComponent>();
	m_pBoxCollision = m_pEnemy->GetComponent<BoxCollision>();
}

void dae::EnemyBubbleState::OnEnter()
{
	m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pBubbleTexture);
	
	m_pBoxCollision->AddIgnoreLayer(0b111);


	RigidBody* pRigidBody{ m_pEnemy->GetComponent<RigidBody>() };
	pRigidBody->SetIgnoreGravity(true);
	pRigidBody->SetVelocity({ 0.0f, 50.0f });

	m_CurrentDuration = 0.0f;
}

void dae::EnemyBubbleState::Update()
{
	// when timer runs out - or bubble hits the top of the level
	// set the enemy back into running
	
	m_CurrentDuration += GameTime::GetInstance().GetDeltaTime();
	auto& localPos{ m_pTransformComp->GetLocalPosition() };
	if (localPos.y <= m_MaxTopPosY || m_CurrentDuration >= m_MaxDuration)
	{
		m_pBoxCollision->RemoveIgnoreLayer(0b111);
		m_pEnemy->GetComponent<RigidBody>()->SetIgnoreGravity(false);
		m_pEnemy->GetComponent<EnemyComponent>()->SetEnemyRunning();
	}


}

void dae::EnemyBubbleState::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pBubbleTexture = newTexture;

	if (m_pEnemy->GetComponent<EnemyComponent>()->GetCurrentState() == this)
	{
		// check if we are already active; if so we need to refresh the textureComponent again
		m_pEnemy->GetComponent<TextureComponent>()->SetTexture(m_pBubbleTexture);
	}

}
