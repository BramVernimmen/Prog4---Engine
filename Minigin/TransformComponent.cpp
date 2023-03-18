#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::TransformComponent::Update()
{
	if (m_NeedsUpdate)
	{
		// when our local has changed
		
		// cache the parent of our owner
		const auto grandParent{ GetOwner().lock()->GetParent().lock() };
		if (grandParent) // if this exists
		{
			SetWorldPosition(grandParent->GetComponent<TransformComponent>()->GetWorldPosition());
		}
		else
		{
			// give empty, the root is always 0,0
			// giving an empty will just add the changed local, and change all children
			SetWorldPosition(glm::vec3{});
		}
	}
}


const glm::vec3& dae::TransformComponent::GetWorldPosition() const
{
	return m_WorldPosition;
}


void dae::TransformComponent::SetLocalPosition(float x, float y)
{
	// setting our local position should also update the world position
	// set the new local
	// mark as "dirty"
	// then in the update, get the world pos from the parent of OUR owner
	// and call SetWorldPosition

	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_NeedsUpdate = true;
}

void dae::TransformComponent::SetWorldPosition(glm::vec3 newWorldPos)
{
	m_WorldPosition = newWorldPos + m_LocalPosition;

	for (const auto& currChild : GetOwner().lock()->GetChildren())
	{
		// check if our owner has other children, their position will need to be changed too
		currChild->GetComponent<TransformComponent>()->SetWorldPosition(m_WorldPosition);
	}
}
