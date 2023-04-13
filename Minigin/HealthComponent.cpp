#include "HealthComponent.h"
#include "EngineEvents.h"

dae::HealthComponent::HealthComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
	ResetHealth();
}

void dae::HealthComponent::Update()
{
}

void dae::HealthComponent::ResetHealth()
{
	m_CurrentHealth = m_MaxHealth;
}

void dae::HealthComponent::DoDamage(int damage)
{
	m_CurrentHealth -= damage;
	if (damage > 0)
	{
		// we took damage, send event
		NotifyObservers(PlayerDamaged(), GetOwner());
	}
}
