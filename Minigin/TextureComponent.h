#pragma once
#include "UpdateComponent.h"
#include "Transform.h"
#include <string>

namespace dae
{
	class Texture2D;
	class RenderComponent;
    class TextureComponent final : public UpdateComponent
    {
    public:
		TextureComponent(std::shared_ptr<GameObject>& pParent);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;


		virtual void Update() override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void AddToRenderer(std::shared_ptr<RenderComponent>& pRenderer);

    private:
		Transform m_Transform{};
		std::shared_ptr<Texture2D> m_pTexture{};
    };

}
