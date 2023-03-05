#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
	m_TransformComponent = pOwner.lock()->GetComponent<TransformComponent>();
}

void dae::TextureComponent::Update()
{
	// handle updates here
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}


void dae::TextureComponent::AddToRenderer(std::shared_ptr<RenderComponent>& pRenderer)
{
	pRenderer->AddTextureToRender(m_pTexture, m_TransformComponent.lock());
}

