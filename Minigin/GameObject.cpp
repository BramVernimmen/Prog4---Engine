#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
{
	AddComponent<TransformComponent>();
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (const auto& currComponent : m_Components)
	{
		currComponent->Update();
	}

	for (auto& currChild : m_Children)
	{
		currChild->Update();
	}
}

void dae::GameObject::Render() const
{
	if (m_RenderComponent)
		m_RenderComponent->Render();

	for (const auto& currChild : m_Children)
	{
		currChild->Render();
	}
}

void dae::GameObject::DisplayGui()
{
	if (m_RenderComponent)
		m_RenderComponent->DisplayGui();

	for (auto& currChild : m_Children)
	{
		currChild->DisplayGui();
	}
}

void dae::GameObject::SetParent(GameObject* newParent, bool keepWorldPosition)
{
	if (this == newParent || newParent == nullptr)
		return;

	// first check if this parent isn't one of our children
	if (CheckIfChild(newParent))
		return;

	std::unique_ptr<GameObject> thisObject;

	if (m_pParent)// we already have a parent, remove ourselves first
	{
		thisObject = std::move(m_pParent->RemoveChild(this));
	}
	else
	{
		thisObject = std::unique_ptr<GameObject>(this);
	}

	


	//update positions
	
	if (keepWorldPosition)
	{
		// cache our transform
		auto transComp{ GetComponent<TransformComponent>() };
		const auto& worldPos{ transComp->GetWorldPosition() - newParent->GetComponent<TransformComponent>()->GetWorldPosition()};
		transComp->SetLocalPosition(worldPos.x, worldPos.y);
	}
	
	

	m_pParent = newParent;
	newParent->AddChild(std::move(thisObject));

}



void dae::GameObject::AddChild(std::unique_ptr<GameObject> newChild)
{
	m_ReturnChildren.emplace_back(newChild.get());
	m_Children.emplace_back(std::move(newChild));
}

std::unique_ptr<dae::GameObject> dae::GameObject::RemoveChild(GameObject* childToRemove)
{
	for (auto it{ m_ReturnChildren.begin() }; it != m_ReturnChildren.end(); ++it)
	{
		if ((*it) == childToRemove)
		{
			m_ReturnChildren.erase(it);
			break;
		}
	}

	for (auto it{ m_Children.begin() }; it != m_Children.end(); ++it)
	{
		if ((*it).get() == childToRemove)
		{
			auto localCopy = std::move((*it));
			m_Children.erase(it);
			return std::move(localCopy);
		}
	}

	return nullptr;
}

bool dae::GameObject::CheckIfChild(GameObject* parentToCheck)
{
	for (const auto& currChild : m_ReturnChildren)
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
