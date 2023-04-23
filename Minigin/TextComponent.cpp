#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TextComponent::TextComponent(GameObject* pOwner)
	:UpdateComponent(pOwner)
{
	m_TransformComponent = GetOwner()->GetComponent<TransformComponent>().get();
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		// first remove the old one, so it won't be stored
		m_pRenderComponent->RemoveTextureFromRenderer(m_pTexture.get(), m_TransformComponent);

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
		m_pRenderComponent->AddTextureToRender(m_pTexture.get(), m_TransformComponent);
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

void dae::TextComponent::SetColor(const SDL_Color& newColor)
{
	m_Color = newColor;
	m_NeedsUpdate = true;
}

void dae::TextComponent::AddToRenderer(RenderComponent* pRenderer)
{
	pRenderer->AddTextureToRender(m_pTexture.get(), m_TransformComponent);
	m_pRenderComponent = pRenderer;
}
