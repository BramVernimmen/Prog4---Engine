#include "MoveCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "GameTime.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject, float speed)
	: m_pGameObject{pGameObject}
	, m_MovementSpeed{speed}
{
	// cache the transform from the gameobject
	m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
}

void dae::MoveCommand::Execute()
{
	// get the direction linked to this command
	auto axisValue = m_InputValue;


	axisValue *= m_MovementSpeed * dae::GameTime::GetInstance().GetDeltaTime();
	const auto& localPos{ m_pTransform->GetLocalPosition() };
	// move the local pos
	m_pTransform->SetLocalPosition(axisValue.x + localPos.x, localPos.y - axisValue.y );
}
