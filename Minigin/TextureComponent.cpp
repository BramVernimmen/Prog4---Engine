#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_TransformComponent = GetOwner()->GetComponent<TransformComponent>();
}

void dae::TextureComponent::Update()
{
	// handle updates here
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	auto pRenderer{ GetOwner()->GetComponent<RenderComponent>() };
	pRenderer->RemoveTextureFromRenderer(m_pTexture.get(), m_TransformComponent);
	m_pTexture = newTexture;
	pRenderer->AddTextureToRender(newTexture.get(), m_TransformComponent);
}


void dae::TextureComponent::AddToRenderer(RenderComponent* pRenderer)
{
	pRenderer->AddTextureToRender(m_pTexture.get(), m_TransformComponent);
}

