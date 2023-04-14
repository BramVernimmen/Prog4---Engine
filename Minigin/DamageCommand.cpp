#include "DamageCommand.h"
#include "GameObject.h"
#include "HealthComponent.h"

dae::DamageCommand::DamageCommand(GameObject* pGameObject, int damage)
	: m_pGameObject{pGameObject}
	, m_Damage{damage}
{
	m_pHealth = pGameObject->GetComponent<HealthComponent>().get();
}

void dae::DamageCommand::Execute()
{
	m_pHealth->DoDamage(m_Damage);
}
