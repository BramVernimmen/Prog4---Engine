#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(std::weak_ptr<GameObject> pOwner)
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
	if (typeid(currEvent) == typeid(PlayerDamaged))
	{
		AddScore(250);
	}
	else if (typeid(currEvent) == typeid(PlayerDied))
	{
		AddScore(2000);
	}
}

