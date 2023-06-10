#include "LivesComponent.h"
#include "GameEvents.h"

dae::LivesComponent::LivesComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	ResetLives();
}



void dae::LivesComponent::ResetLives()
{
	m_CurrentLives = m_MaxLives;
}

void dae::LivesComponent::RemoveLife()
{
	if (m_CurrentLives <= 0) // player is dead
		return;

	--m_CurrentLives;
	
	if (m_CurrentLives <= 0) // player has died
	{
		m_CurrentLives = 0; // safe reset to 0
		// send death event
		NotifyObservers(PlayerDied());
		// don't return as we also took a hit, so we need to send an event for that too
	}

	// we lost a live, send event
	NotifyObservers(PlayerHit(), this);
	
}
