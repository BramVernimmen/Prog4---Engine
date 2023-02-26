#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextureComponent::TextureComponent(std::shared_ptr<GameObject>& pParent)
	: UpdateComponent(pParent)
{
}

void dae::TextureComponent::Update()
{
	// handle updates here
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::TextureComponent::AddToRenderer(std::shared_ptr<RenderComponent>& pRenderer)
{
	pRenderer->AddTextureToRender(m_pTexture, m_Transform);
}

