#include "RenderComponent.h"
#include "Transform.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(std::shared_ptr<GameObject>& pParent)
	: BaseComponent(pParent)
{
}

void dae::RenderComponent::Render() const
{
	for (const auto& currElement : m_TexturesToRenderMap)
	{
		if (currElement.first.get() == nullptr)
			continue;
		const auto& currPosition{ currElement.second.GetPosition() };
		Renderer::GetInstance().RenderTexture(*currElement.first, currPosition.x, currPosition.y);
	}

}

void dae::RenderComponent::AddTextureToRender(std::shared_ptr<Texture2D> pTextureToAdd, Transform transform)
{
	m_TexturesToRenderMap.insert({ pTextureToAdd, transform });
}

void dae::RenderComponent::RemoveTextureFromRenderer(std::shared_ptr<Texture2D> pTextureToRemove, Transform transform)
{
	for (auto it{ m_TexturesToRenderMap.begin() }; it != m_TexturesToRenderMap.end(); ++it)
	{
		if (it->first == pTextureToRemove && it->second.GetPosition() == transform.GetPosition())
		{
			// we found the pair that we want to erase
			m_TexturesToRenderMap.erase(it);
			return;
		}
	}
}

