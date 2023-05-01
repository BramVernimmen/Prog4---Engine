#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "imgui.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void dae::RenderComponent::Render() const
{
	auto& renderer = Renderer::GetInstance();
	for (const auto& currElement : m_TexturesToRenderMap)
	{
		if (currElement.first == nullptr)
			continue;
		const auto& currPosition{ currElement.second->GetWorldPosition()};
		renderer.RenderTexture(*currElement.first, currPosition.x, currPosition.y);
	}

	if (!renderer.DrawDebug())
		return;
	for (const auto& currDebug : m_DebugComponents)
	{
		if (currDebug)
		{
			currDebug->Render();
		}
	}
}

void dae::RenderComponent::DisplayGui()
{
	for (auto& currComponent : m_DisplayGuiComponents)
	{
		currComponent->DisplayGui();
	}
}

void dae::RenderComponent::AddTextureToRender(Texture2D* pTextureToAdd, TransformComponent* pTransform)
{
	m_TexturesToRenderMap.insert({ pTextureToAdd, pTransform });
}

void dae::RenderComponent::RemoveTextureFromRenderer(Texture2D* pTextureToRemove, TransformComponent* pTransform)
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



void dae::RenderComponent::AddToDisplayGui(UpdateComponent* pComponentToAdd)
{
	//auto findResult{ std::find(m_DisplayGuiComponents.begin(), m_DisplayGuiComponents.end(), pComponentToAdd) };
	//if ( findResult == m_DisplayGuiComponents.end())// if we reach the end, add it
	//	m_DisplayGuiComponents.push_back(pComponentToAdd);

	auto foundIt = std::find_if(m_DisplayGuiComponents.begin(), m_DisplayGuiComponents.end(), [pComponentToAdd](UpdateComponent* currElement)
		{ return currElement == pComponentToAdd; });

	if (foundIt == m_DisplayGuiComponents.end()) // if we reach the end, add it
		m_DisplayGuiComponents.emplace_back(pComponentToAdd);
	// else don't do anything, it's already in there
}

void dae::RenderComponent::RemoveFromDisplayGui(UpdateComponent* pComponentToAdd)
{
	auto foundIt = std::find_if(m_DisplayGuiComponents.begin(), m_DisplayGuiComponents.end(), [pComponentToAdd](UpdateComponent* currElement)
		{ return currElement == pComponentToAdd; });

	if (foundIt != m_DisplayGuiComponents.end()) // if we don't reach the end, remove it
		m_DisplayGuiComponents.erase(foundIt);
}

void dae::RenderComponent::AddToDebug(UpdateComponent* pComponentToAdd)
{
	auto foundIt = std::find_if(m_DebugComponents.begin(), m_DebugComponents.end(), [pComponentToAdd](UpdateComponent* currElement)
		{ return currElement == pComponentToAdd; });

	if (foundIt == m_DebugComponents.end()) // if we reach the end, add it
		m_DebugComponents.emplace_back(pComponentToAdd);
}

void dae::RenderComponent::RemoveFromDebug(UpdateComponent* pComponentToAdd)
{
	auto foundIt = std::find_if(m_DebugComponents.begin(), m_DebugComponents.end(), [pComponentToAdd](UpdateComponent* currElement)
		{ return currElement == pComponentToAdd; });

	if (foundIt != m_DebugComponents.end()) // if we don't reach the end, remove it
		m_DisplayGuiComponents.erase(foundIt);
}

