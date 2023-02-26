#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"

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
	for (const auto& currComponent : m_Components)
	{
		currComponent->Render();
	}
}