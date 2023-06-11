#include "MoveCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerComponent.h"
#include "PlayerState.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject)
	: m_pGameObject{pGameObject}
{
	m_pPlayerComponent = m_pGameObject->GetComponent<PlayerComponent>();
}

void dae::MoveCommand::Execute()
{
	GameObject* pSceneRoot{ SceneManager::GetInstance().GetActiveScene()->GetRoot() };
	if (m_pGameObject->GetRootObject() != pSceneRoot)
		return;

	m_pPlayerComponent->GetCurrentState()->HandleInput(m_InputValue);
}
