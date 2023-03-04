#pragma once
#include "BaseComponent.h"
#include <unordered_map>
namespace dae
{
	class Transform;
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(std::weak_ptr<GameObject> pParent);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update() override {}
		virtual void Render() const override;

		void AddTextureToRender(std::shared_ptr<Texture2D> pTextureToAdd, Transform transform);
		void RemoveTextureFromRenderer(std::shared_ptr<Texture2D> pTextureToRemove, Transform transform);

	protected:

	private:
		std::unordered_multimap<std::shared_ptr<Texture2D>, Transform> m_TexturesToRenderMap{};
	};
}

