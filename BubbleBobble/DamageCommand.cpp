#include "DamageCommand.h"
#include "GameObject.h"
#include "LivesComponent.h"

dae::DamageCommand::DamageCommand(GameObject* pGameObject)
	: m_pGameObject{pGameObject}
{
	m_pLives = pGameObject->GetComponent<LivesComponent>();
}

void dae::DamageCommand::Execute()
{
	m_pLives->RemoveLife();
}
