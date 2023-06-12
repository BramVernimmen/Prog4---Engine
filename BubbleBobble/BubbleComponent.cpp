#include "BubbleComponent.h"
#include "GameTime.h"
#include "GameObject.h"
#include "EnemyComponent.h"
#include "EnemyBubbleState.h"
#include "RigidBody.h"
#include <glm/glm.hpp>

dae::BubbleComponent::BubbleComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pRigidBody = GetOwner()->GetComponent<RigidBody>();
}

void dae::BubbleComponent::Update()
{
	if (m_CurrentTimeAlive < m_MaxLifeTime)
	{
		const float dt{ GameTime::GetInstance().GetDeltaTime() };
		m_CurrentTimeAlive += dt;
		auto currVelocity{ m_pRigidBody->GetVelocity() };
		const float xModifier{ 40.0f };
		const float yModifier{ 200.0f };
		if (currVelocity.x < 0.0f)
		{
			// bubble going left
			currVelocity.x -= dt * xModifier;
		}
		else
		{
			currVelocity.x += dt * xModifier;
		}

		currVelocity.y += dt * yModifier;
		m_pRigidBody->SetVelocity(currVelocity);
	}
	else
	{
		GetOwner()->MarkForDelete();
	}
}

void dae::BubbleComponent::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(ObjectOverlapping)) // handle things here
	{
		if (payload.type() == typeid(GameObject*))
		{
			EnemyComponent* pEnemyComp{ std::any_cast<GameObject*>(payload)->GetComponent<EnemyComponent>() };
			if (pEnemyComp)
			{
				// we should only be able to overlap with non dead - non bubbled enemies
				if (!(dynamic_cast<EnemyBubbleState*>(pEnemyComp->GetCurrentState()))) 
				{
					pEnemyComp->SetEnemyBubble();
					GetOwner()->MarkForDelete();
				}

			}
		}
	}
}
