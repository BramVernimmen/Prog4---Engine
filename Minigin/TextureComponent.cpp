#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_TransformComponent = GetOwner()->GetComponent<TransformComponent>().get();
}

void dae::TextureComponent::Update()
{
	// handle updates here
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}


void dae::TextureComponent::AddToRenderer(RenderComponent* pRenderer)
{
	pRenderer->AddTextureToRender(m_pTexture.get(), m_TransformComponent);
}

