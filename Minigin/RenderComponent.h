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
		RenderComponent(GameObject* pOwner);
		~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update() override {}
		virtual void Render() const override;
		virtual void DisplayGui() override;

		void AddTextureToRender(Texture2D* pTextureToAdd, TransformComponent* pTransform);
		void RemoveTextureFromRenderer(Texture2D* pTextureToRemove, TransformComponent* pTransform);

		void AddToDisplayGui(UpdateComponent* pComponentToAdd);
		void RemoveFromDisplayGui(UpdateComponent* pComponentToAdd);

	protected:

	private:
		// this map shouldn't have full ownership, yet weird things happen if I try to make this weak_ptrs instead
		std::unordered_multimap<Texture2D*, TransformComponent*> m_TexturesToRenderMap{};
		std::vector<UpdateComponent*> m_DisplayGuiComponents{};
	};
}

