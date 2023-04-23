#include "DebugHealthComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"

dae::DebugHealthComponent::DebugHealthComponent(GameObject* pOwner)
	: UpdateComponent{pOwner}
{
	m_pPersonalTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void dae::DebugHealthComponent::Update()
{
	if (m_ShouldUpdateText)
	{
		m_pPersonalTextComponent->SetText("Lives: " + std::to_string(m_LastHealth) );
		m_ShouldUpdateText = false;
	}
}

void dae::DebugHealthComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(PlayerDamaged)) // handle things here
	{
		if (payload.type() == typeid(HealthComponent*))
		{
			// handle payload
			int currentHealth{ std::any_cast<HealthComponent*>(payload)->GetCurrentHealth() };
			if (currentHealth != m_LastHealth)
			{
				m_LastHealth = currentHealth;
				m_ShouldUpdateText = true;
			}
		}
	}
}

void dae::DebugHealthComponent::SetLastHealth(int lastHealth)
{
	m_LastHealth = lastHealth; 
	m_ShouldUpdateText = true;
}
