#pragma once
#include "UpdateComponent.h"
#include <string>
#include <SDL_pixels.h>

namespace dae
{
	//class SDL_Pixels;
	class Font;
	class Texture2D;
	class RenderComponent;
	class TransformComponent;
	class TextComponent final : public UpdateComponent
	{
		
	public:
		TextComponent(GameObject* pOwner);
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


		virtual void Update() override;

		void SetFont(std::shared_ptr<Font>& newFont);
		void SetText(const std::string& newText);
		//void SetPosition(float x, float y);
		void SetColor(const SDL_Color& newColor);

		void AddToRenderer(RenderComponent* pRenderer);

	private:
		RenderComponent* m_pRenderComponent{};
		TransformComponent* m_TransformComponent{};
		std::shared_ptr<Texture2D> m_pTexture{};

		bool m_NeedsUpdate{true};
		std::string m_Text{};
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color{ 255,255,255 };
	};
}


