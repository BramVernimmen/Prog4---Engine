#pragma once
#include "BaseComponent.h"
#include <unordered_map>
namespace dae
{
	class TransformComponent;
	class Texture2D;
	class UpdateComponent;
	class RenderComponent final: public BaseComponent
	{
	public:
		RenderComponent(std::weak_ptr<GameObject> pOwner);
		~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update() override {}
		virtual void Render() const override;
		virtual void DisplayGui() override;

		void AddTextureToRender(std::shared_ptr<Texture2D> pTextureToAdd, std::shared_ptr<TransformComponent> pTransform);
		void RemoveTextureFromRenderer(std::shared_ptr<Texture2D> pTextureToRemove, std::shared_ptr<TransformComponent> pTransform);

		void AddToDisplayGui(std::weak_ptr<UpdateComponent> pComponentToAdd);
		void RemoveFromDisplayGui(std::weak_ptr<UpdateComponent> pComponentToAdd);

	protected:

	private:
		// this map shouldn't have full ownership, yet weird things happen if I try to make this weak_ptrs instead
		std::unordered_multimap<std::shared_ptr<Texture2D>, std::shared_ptr<TransformComponent>> m_TexturesToRenderMap{};
		std::vector<std::weak_ptr<UpdateComponent>> m_DisplayGuiComponents{};
	};
}

