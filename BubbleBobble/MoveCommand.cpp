#include "MoveCommand.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "GameTime.h"
#include "BoxCollision.h"
#include "CollisionManager.h"
#include <SDL_rect.h>
#include "Uitls.h"
#include <iostream>

dae::MoveCommand::MoveCommand(GameObject* pGameObject, float speed)
	: m_pGameObject{pGameObject}
	, m_MovementSpeed{speed}
{
	// cache the transform from the gameobject
	m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	m_pBoxCollision = m_pGameObject->GetComponent<BoxCollision>();
}

void dae::MoveCommand::Execute()
{
	// get the direction linked to this command
	auto axisValue = m_InputValue;


	axisValue *= m_MovementSpeed * dae::GameTime::GetInstance().GetDeltaTime();
	const auto& localPos{ m_pTransform->GetLocalPosition() };
	// move the local pos
	m_pTransform->SetLocalPosition(axisValue.x + localPos.x, localPos.y - axisValue.y );

	const SDL_Rect& hit = dae::CollisionManager::GetInstance().CheckCollision(m_pBoxCollision);
	if (hit.w > 0) // we have a hit
	{
		const SDL_Rect& currBox = m_pBoxCollision->GetRect();

		// add displacement code here
		
	}

}
