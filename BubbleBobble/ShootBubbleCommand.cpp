#include "ShootBubbleCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerComponent.h"
#include "PlayerRunningState.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

#include <iostream>

dae::ShootBubbleCommand::ShootBubbleCommand(GameObject* pGameObject, unsigned short shootId, float shootForce)
	: m_pGameObject{pGameObject}
	, m_ShootSoundId{shootId}
	, m_ShootForce{shootForce}
{
	m_pPlayerComponent = m_pGameObject->GetComponent<PlayerComponent>();
}

void dae::ShootBubbleCommand::Execute()
{
	GameObject* pSceneRoot{ SceneManager::GetInstance().GetActiveScene()->GetRoot() };
	if (m_pGameObject->GetRootObject() != pSceneRoot) // only shoot bubbles when we are actually in the scene
		return;

	PlayerRunningState* pRunningState{ dynamic_cast<PlayerRunningState*>(m_pPlayerComponent->GetCurrentState()) };
	if (pRunningState && pRunningState->CanShoot())
	{
		ServiceLocator::GetSoundSystem().Play(m_ShootSoundId);
		// spawn bubble
		std::cout << "SHOOT\n";
		pRunningState->Shoot();
		// add force to it
	}

}
