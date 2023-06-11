#pragma once
#include "UpdateComponent.h"
#include <string>

namespace dae
{
	class Texture2D;
	class RenderComponent;
	class TransformComponent;
    class TextureComponent final : public UpdateComponent
    {
    public:
		TextureComponent(GameObject* pOwner);
		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;


		virtual void Update() override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		std::shared_ptr<Texture2D> GetTexture() { return m_pTexture; }

		void AddToRenderer(RenderComponent* pRenderer);

    private:
		std::shared_ptr<Texture2D> m_pTexture{nullptr};
		TransformComponent* m_TransformComponent{};
    };

}
