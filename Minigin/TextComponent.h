#pragma once
#include "UpdateComponent.h"
#include "Transform.h"
#include <string>
#include <SDL_pixels.h>

namespace dae
{
	//class SDL_Pixels;
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent : public UpdateComponent
	{
		
	public:
		TextComponent(std::weak_ptr<GameObject> pParent);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


		virtual void Update() override;

		void SetFont(std::shared_ptr<Font>& newFont);
		void SetText(const std::string& newText);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& newColor);

		void AddToRenderer(std::shared_ptr<RenderComponent>& pRenderer);

	private:
		std::weak_ptr<RenderComponent> m_pRenderComponent{};
		Transform m_Transform{};
		std::shared_ptr<Texture2D> m_pTexture{};

		bool m_NeedsUpdate{true};
		std::string m_Text{};
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color{ 255,255,255 };
	};
}


