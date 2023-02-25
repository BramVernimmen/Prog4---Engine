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
		const auto& currPosition{ currElement.second.GetPosition() };
		Renderer::GetInstance().RenderTexture(*currElement.first, currPosition.x, currPosition.y);
	}
}

void dae::RenderComponent::AddTextureToRender(std::shared_ptr<Texture2D> pTextureToAdd, Transform transform)
{
	m_TexturesToRenderMap.insert({ pTextureToAdd, transform });

	// to remove from map, in destructor of certain components: https://stackoverflow.com/questions/3952476/how-to-remove-a-specific-pair-from-a-c-multimap
}

