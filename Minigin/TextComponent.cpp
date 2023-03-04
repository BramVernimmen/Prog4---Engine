#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"
//#include <SDL_pixels.h>
#include "Renderer.h"

dae::TextComponent::TextComponent(std::weak_ptr<GameObject> pParent)
	:UpdateComponent(pParent)
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		// first remove the old one, so it won't be stored
		m_pRenderComponent.lock()->RemoveTextureFromRenderer(m_pTexture, m_Transform);

		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;

		// then add the new one
		m_pRenderComponent.lock()->AddTextureToRender(m_pTexture, m_Transform);
	}
}

void dae::TextComponent::SetFont(std::shared_ptr<Font>& newFont)
{
	m_Font = std::move(newFont);
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::TextComponent::SetColor(const SDL_Color& newColor)
{
	m_Color = newColor;
	m_NeedsUpdate = true;
}

void dae::TextComponent::AddToRenderer(std::shared_ptr<RenderComponent>& pRenderer)
{
	pRenderer->AddTextureToRender(m_pTexture, m_Transform);
	m_pRenderComponent = pRenderer;
}
