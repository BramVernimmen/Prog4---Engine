#include "DebugLivesComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "LivesComponent.h"

dae::DebugLivesComponent::DebugLivesComponent(GameObject* pOwner)
	: UpdateComponent{pOwner}
{
	m_pPersonalTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void dae::DebugLivesComponent::Update()
{
	if (m_ShouldUpdateText)
	{
		
		m_pPersonalTextComponent->SetText("Lives: " + std::to_string((m_LastLives > 0) ? m_LastLives - 1 : m_LastLives));
		m_ShouldUpdateText = false;
	}
}

void dae::DebugLivesComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(PlayerHit)) // handle things here
	{
		if (payload.type() == typeid(LivesComponent*))
		{
			// handle payload
			int currentLives{ std::any_cast<LivesComponent*>(payload)->GetCurrentLives() };
			if (currentLives != m_LastLives)
			{
				m_LastLives = currentLives;
				m_ShouldUpdateText = true;
			}
		}
	}
}

void dae::DebugLivesComponent::SetLastLives(int lastLives)
{
	m_LastLives = lastLives;
	m_ShouldUpdateText = true;
}
