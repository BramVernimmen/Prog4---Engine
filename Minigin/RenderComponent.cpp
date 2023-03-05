#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"

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

