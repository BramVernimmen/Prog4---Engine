#include "HealthComponent.h"
#include "EngineEvents.h"

dae::HealthComponent::HealthComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	ResetHealth();
}



void dae::HealthComponent::ResetHealth()
{
	m_CurrentHealth = m_MaxHealth;
}

void dae::HealthComponent::DoDamage(int damage)
{
	if (m_CurrentHealth <= 0) // player is dead
		return;

	m_CurrentHealth -= damage;
	if (damage > 0)
	{
		if (m_CurrentHealth <= 0) // player has died
		{
			m_CurrentHealth = 0; // safe reset to 0
			// send death event
			NotifyObservers(PlayerDied());
		}

		// we took damage, send event
		NotifyObservers(PlayerDamaged(), this);
	}

	
}
