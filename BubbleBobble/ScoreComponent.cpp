#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{

}

void dae::ScoreComponent::AddScore(int scoreToAdd)
{
	m_CurrentScore += scoreToAdd;

	// notify that score has been given
	NotifyObservers(GainedScore(), this);
}

void dae::ScoreComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(PlayerHit))
	{
		AddScore(250);
	}
	else if (typeid(currEvent) == typeid(PlayerDied))
	{
		AddScore(2000);
	}
}

