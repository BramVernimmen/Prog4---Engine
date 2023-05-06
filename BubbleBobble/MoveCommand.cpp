#include "MoveCommand.h"
#include "GameObject.h"
//#include "TransformComponent.h"
#include "RigidBody.h"
#include "InputManager.h"
#include "GameTime.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject, float speed, float jumpStrength)
	: m_pGameObject{pGameObject}
	, m_MovementSpeed{speed}
	, m_JumpStrength{jumpStrength}
{
	// cache the transform from the gameobject
	//m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	m_pRigidBody = m_pGameObject->GetComponent<RigidBody>();
}

void dae::MoveCommand::Execute()
{
	// ----------- USING TRANSLATION ---------
	// get the direction linked to this command

	/*
	auto axisValue = m_InputValue;


	axisValue *= m_MovementSpeed * dae::GameTime::GetInstance().GetDeltaTime();
	const auto& localPos{ m_pTransform->GetLocalPosition() };
	// move the local pos
	m_pTransform->SetLocalPosition(axisValue.x + localPos.x, localPos.y - axisValue.y );
	*/

	// ---------------------------------------

	// ----------- USING RIGIDBODY ---------

	if (m_pRigidBody->IsGrounded() == false)
		return;

	auto axisValue = m_InputValue; // we will only use left, right and up
	if (axisValue.y < 0.0f)
		axisValue.y = 0.0f;
	//const float dt = dae::GameTime::GetInstance().GetDeltaTime();

	axisValue.x *= m_MovementSpeed;
	axisValue.y *= m_JumpStrength;
	

	const auto& currVelocity = m_pRigidBody->GetVelocity();
	m_pRigidBody->SetVelocity({ axisValue.x, currVelocity.y + axisValue.y });
	m_pRigidBody->SetGrounded(false);
}
