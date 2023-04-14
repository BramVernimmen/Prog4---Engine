#include "DebugScoreComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::DebugScoreComponent::DebugScoreComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
	m_pPersonalTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void dae::DebugScoreComponent::Update()
{
	if (m_ShouldUpdateText)
	{
		m_pPersonalTextComponent.lock()->SetText("Score: " + std::to_string(m_CurrentScoreToPrint));
	}
}

void dae::DebugScoreComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(GainedScore)) // handle things here
	{
		if (payload.type() == typeid(ScoreComponent*))
		{
			// handle payload
			int currentScore{ std::any_cast<ScoreComponent*>(payload)->GetCurrentScore() };
			if (currentScore != m_CurrentScoreToPrint)
			{
				m_CurrentScoreToPrint = currentScore;
				m_ShouldUpdateText = true;
			}
		}
	}
}