#include "MoveCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject, float speed)
	: Command(pGameObject)
	, m_MovementSpeed{speed}
{
	// cache the transform from the gameobject
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>().get();
}

void dae::MoveCommand::Execute()
{
	// get the direction linked to this command
	auto axisValue = dae::InputManager::GetInstance().Get2DAxisValue();

	axisValue *= m_MovementSpeed * dae::Time::GetInstance().GetDeltaTime();
	const auto& localPos{ m_pTransform->GetLocalPosition() };
	// move the local pos
	m_pTransform->SetLocalPosition(axisValue.x + localPos.x, localPos.y - axisValue.y );
}
