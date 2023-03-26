#include "MoveCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"

dae::MoveCommand::MoveCommand(std::weak_ptr<GameObject> pGameObject, float speed)
	: m_pGameObject{pGameObject}
	, m_MovementSpeed{speed}
{
	// cache the transform from the gameobject
	m_pTransform = m_pGameObject.lock()->GetComponent<TransformComponent>();
}

void dae::MoveCommand::Execute()
{
	// get the direction linked to this command
	auto axisValue = dae::InputManager::GetInstance().Get2DAxisValue();

	axisValue *= m_MovementSpeed * dae::Time::GetInstance().GetDeltaTime();
	auto lockedTransform{ m_pTransform.lock() };
	const auto localPos{ lockedTransform->GetLocalPosition() };
	// move the local pos
	lockedTransform->SetLocalPosition(axisValue.x + localPos.x, localPos.y - axisValue.y );
}
