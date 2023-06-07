#include "MoveCommand.h"
#include "GameObject.h"
//#include "TransformComponent.h"
#include "RigidBody.h"
#include "InputManager.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "BoxCollision.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "Scene.h"


dae::MoveCommand::MoveCommand(GameObject* pGameObject, float speed, float jumpStrength, unsigned short jumpSoundID, const std::string& jumpSoundPath)
	: m_pGameObject{pGameObject}
	, m_MovementSpeed{speed}
	, m_JumpStrength{jumpStrength}
	, m_JumpSoundID{jumpSoundID}
{
	// cache the transform from the gameobject
	//m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	m_pRigidBody = m_pGameObject->GetComponent<RigidBody>();
	m_pBoxCollision = m_pGameObject->GetComponent<BoxCollision>();
	m_pRenderComponent = m_pGameObject->GetComponent<RenderComponent>();
	dae::ServiceLocator::GetSoundSystem().Load(m_JumpSoundID, jumpSoundPath);
}

void dae::MoveCommand::Execute()
{
	GameObject* pSceneRoot{ SceneManager::GetInstance().GetActiveScene()->GetRoot() };
	if (m_pGameObject->GetRootObject() != pSceneRoot)
		return;


	if (m_pRigidBody->GetVelocity().y > 0.0f)
	{
		m_pBoxCollision->AddIgnoreLayer(0b10);
	}
	else
	{
		m_pBoxCollision->RemoveIgnoreLayer(0b10);
	}

	if (m_pRigidBody->IsGrounded() == false)
		return;

	auto axisValue = m_InputValue; // we will only use left, right and up
	if (axisValue.y <= 0.0f)
		axisValue.y = 0.0f;
	else
		dae::ServiceLocator::GetSoundSystem().Play(m_JumpSoundID);


	axisValue.x *= m_MovementSpeed;
	axisValue.y *= m_JumpStrength;
	
	if (axisValue.x > 0)
	{
		m_pRenderComponent->SetFlipTexutures(false);
	} 
	else if (axisValue.x < 0)
	{
		m_pRenderComponent->SetFlipTexutures(true);
	}

	const auto& currVelocity = m_pRigidBody->GetVelocity();
	m_pRigidBody->SetVelocity({ axisValue.x, currVelocity.y + axisValue.y });
	m_pRigidBody->SetGrounded(false);
}
