#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::TransformComponent::Update()
{
	
}


const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_IsDirty)
		UpdateWorldPosition();

	return m_WorldPosition;
}

void dae::TransformComponent::UpdateWorldPosition()
{
	// when our local has changed

	// cache the parent of our owner
	const auto grandParent{ GetOwner()->GetParent().lock() };
	if (grandParent) // if this exists
	{
		SetWorldPosition(grandParent->GetComponent<TransformComponent>()->GetWorldPosition());
	}
	else
	{
		// given when empty, the root is always 0,0
		// giving an empty will just add the changed local, and change all children
		SetWorldPosition(glm::vec3{});
	}
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
	m_IsDirty = true;
}

void dae::TransformComponent::SetWorldPosition(glm::vec3 newWorldPos)
{
	m_WorldPosition = newWorldPos + m_LocalPosition;

	for (const auto& currChild : GetOwner()->GetChildren())
	{
		// check if our owner has other children
		// their position will need to be changed too
		// set them as dirt, next update they will correct their own position
		currChild->GetComponent<TransformComponent>()->SetDirty();
	}
}

void dae::TransformComponent::SetDirty()
{
	m_IsDirty = true;

	// we continue this chain until there are no more children left
	for (const auto& currChild : GetOwner()->GetChildren())
	{
		currChild->GetComponent<TransformComponent>()->SetDirty();
	}
}
