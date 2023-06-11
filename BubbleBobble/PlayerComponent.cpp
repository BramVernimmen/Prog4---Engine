#include "PlayerComponent.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerManager.h"
#include "BoxCollision.h"

dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::PlayerComponent::Update()
{
	// handle states here

}

void dae::PlayerComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(ObjectOverlapping)) // handle things here
	{
		if (payload.type() == typeid(GameObject*))
		{
			if (std::any_cast<GameObject*>(payload)->GetComponent<PlayerComponent>())
			{
				NotifyObservers(PlayerHit());
				PlayerManager::GetInstance().RespawnPlayer(GetOwner(), m_PlayerId);
				NotifyObservers(ItemPickedUp(), 200);
			}
		}
	}
	if (typeid(currEvent) == typeid(PlayerDied))
	{
		// set to dead state, this is just a temp test
		GetOwner()->GetComponent<RigidBody>()->SetKinematic(true);
		GetOwner()->GetComponent<BoxCollision>()->SetInactive();
	}
}

