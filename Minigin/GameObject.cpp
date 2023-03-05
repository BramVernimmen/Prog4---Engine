#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (const auto& currComponent : m_Components)
	{
		currComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	m_RenderComponent->Render();
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> newParent)
{
	if (shared_from_this() == newParent)
		return;
	// first check if this parent isn't one of our children
	if (CheckIfChild(newParent))
		return;

	if (m_pParent.lock())// we already have a parent, remove ourselves first
	{
		m_pParent.lock()->RemoveChild(shared_from_this());
	}

	m_pParent = newParent;
	newParent->AddChild(shared_from_this());

	//update positions
	if (newParent) // if newParent is not null (is not the scene root)
	{
		// reset the world position of our transform
		// this will chain to all our children
		GetComponent<TransformComponent>()->SetWorldPosition(newParent->GetComponent<TransformComponent>()->GetWorldPosition());
	}
	else
	{
		// cache our transform
		auto transComp{ GetComponent<TransformComponent>() };
		const auto& worldPos{ transComp->GetWorldPosition() };
		transComp->SetLocalPosition(worldPos.x, worldPos.y);
	}
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> newChild)
{
	m_Children.push_back(newChild);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> childToRemove)
{
	for (auto it{ m_Children.begin() }; it != m_Children.end(); ++it)
	{
		if (std::dynamic_pointer_cast<GameObject>(*it) == childToRemove)
		{
			m_Children.erase(it);
			return;
		}
	}
}

bool dae::GameObject::CheckIfChild(std::shared_ptr<GameObject> parentToCheck)
{
	for (const auto& currChild : m_Children)
	{
		// check the child first
		if (currChild == parentToCheck)
			return true;
		// if it doesn't match, check their children
		if (currChild->CheckIfChild(parentToCheck))
			return true;
	}
	return false;
}
