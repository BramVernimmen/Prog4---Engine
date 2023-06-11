#include "PlayerDeathState.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "PlayerComponent.h"
#include "RigidBody.h"
#include "BoxCollision.h"

dae::PlayerDeathState::PlayerDeathState(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
	m_pRenderComp = pPlayer->GetComponent<RenderComponent>();
}

void dae::PlayerDeathState::OnEnter()
{
	m_pPlayer->GetComponent<TextureComponent>()->SetTexture(m_pDeathTexture);
	m_pPlayer->GetComponent<RigidBody>()->SetKinematic(true);
	m_pPlayer->GetComponent<BoxCollision>()->SetInactive();
}

void dae::PlayerDeathState::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pDeathTexture = newTexture;

	if (m_pPlayer->GetComponent<PlayerComponent>()->GetCurrentState() == this)
	{
		// check if we are already active; if so we need to refresh the textureComponent again
		m_pPlayer->GetComponent<TextureComponent>()->SetTexture(m_pDeathTexture);
	}
}
