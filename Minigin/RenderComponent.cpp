#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "imgui.h"

dae::RenderComponent::RenderComponent(std::weak_ptr<GameObject> pOwner)
	: BaseComponent(pOwner)
{
}

void dae::RenderComponent::Render() const
{
	for (const auto& currElement : m_TexturesToRenderMap)
	{
		if (currElement.first.get() == nullptr)
			continue;
		const auto& currPosition{ currElement.second->GetWorldPosition()};
		Renderer::GetInstance().RenderTexture(*currElement.first, currPosition.x, currPosition.y);
	}
}

void dae::RenderComponent::DisplayGui()
{
	for (auto& currComponent : m_DisplayGuiComponents)
	{
		currComponent.lock()->DisplayGui();
	}
}

void dae::RenderComponent::AddTextureToRender(std::shared_ptr<Texture2D> pTextureToAdd, std::shared_ptr<TransformComponent> pTransform)
{
	m_TexturesToRenderMap.insert({ pTextureToAdd, pTransform });
}

void dae::RenderComponent::RemoveTextureFromRenderer(std::shared_ptr<Texture2D> pTextureToRemove, std::shared_ptr<TransformComponent> pTransform)
{
	for (auto it{ m_TexturesToRenderMap.begin() }; it != m_TexturesToRenderMap.end(); ++it)
	{
		if (it->first == pTextureToRemove && it->second->GetWorldPosition() == pTransform->GetWorldPosition())
		{
			// we found the pair that we want to erase
			m_TexturesToRenderMap.erase(it);
			return;
		}
	}
}

void dae::RenderComponent::AddToDisplayGui(std::weak_ptr<UpdateComponent> pComponentToAdd)
{
	//auto findResult{ std::find(m_DisplayGuiComponents.begin(), m_DisplayGuiComponents.end(), pComponentToAdd) };
	//if ( findResult == m_DisplayGuiComponents.end())// if we reach the end, add it
	//	m_DisplayGuiComponents.push_back(pComponentToAdd);

	auto foundIt = std::find_if(m_DisplayGuiComponents.begin(), m_DisplayGuiComponents.end(), [pComponentToAdd](const std::weak_ptr<UpdateComponent>& currElement) 
		{ return currElement.lock() == pComponentToAdd.lock(); });

	if (foundIt == m_DisplayGuiComponents.end()) // if we reach the end, add it
		m_DisplayGuiComponents.push_back(pComponentToAdd);
	// else don't do anything, it's already in there
}

void dae::RenderComponent::RemoveFromDisplayGui(std::weak_ptr<UpdateComponent> pComponentToAdd)
{

	auto foundIt = std::find_if(m_DisplayGuiComponents.begin(), m_DisplayGuiComponents.end(), [pComponentToAdd](const std::weak_ptr<UpdateComponent>& currElement)
		{ return currElement.lock() == pComponentToAdd.lock(); });

	if (foundIt != m_DisplayGuiComponents.end()) // if we don't reach the end, remove it
		m_DisplayGuiComponents.erase(foundIt);
}

