#include "ShootBubbleCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerComponent.h"
#include "PlayerRunningState.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxCollision.h"
#include "RigidBody.h"
#include "BubbleComponent.h"


dae::ShootBubbleCommand::ShootBubbleCommand(GameObject* pGameObject, unsigned short shootId, float shootForce)
	: m_pGameObject{pGameObject}
	, m_ShootSoundId{shootId}
	, m_ShootForce{shootForce}
{
	m_pPlayerComponent = m_pGameObject->GetComponent<PlayerComponent>();
}

void dae::ShootBubbleCommand::Execute()
{
	GameObject* pSceneRoot{ SceneManager::GetInstance().GetActiveScene()->GetRoot() };
	if (m_pGameObject->GetRootObject() != pSceneRoot) // only shoot bubbles when we are actually in the scene
		return;

	PlayerRunningState* pRunningState{ dynamic_cast<PlayerRunningState*>(m_pPlayerComponent->GetCurrentState()) };
	if (pRunningState && pRunningState->CanShoot())
	{
		ServiceLocator::GetSoundSystem().Play(m_ShootSoundId);
		// spawn bubble
		pRunningState->Shoot();
		auto& localPos{ m_pGameObject->GetComponent<TransformComponent>()->GetLocalPosition() };

		GameObject* bubble = new GameObject();
		bubble->SetParent(pSceneRoot);
		auto renderComp = bubble->AddComponent<RenderComponent>();
		bubble->GetComponent<TransformComponent>()->SetLocalPosition(localPos.x, localPos.y);
		auto textureComp = bubble->AddComponent<TextureComponent>();
		textureComp->SetTexture(m_pBubbleTexture);
		textureComp->AddToRenderer(renderComp);
		auto rigidBody = bubble->AddComponent<RigidBody>();
		auto bubbleComp = bubble->AddComponent<BubbleComponent>();
		auto boxCollision = bubble->AddComponent<BoxCollision>();
		boxCollision->SetSize(48, 48);
		boxCollision->SetCurrentLayer(0b10'000);
		boxCollision->AddIgnoreLayer(0b110'011); // grid layers + player + other bubbles
		boxCollision->AddLayerForOverlapEvent(0b100); // enemy layer
		boxCollision->AddObserver(bubbleComp);
		renderComp->AddToDebug(boxCollision);
		rigidBody->SetIgnoreGravity(true);

		// we know the character faces right default, so if textures are flipped, shoot left, if not shoot right
		bool shootLeft{ m_pGameObject->GetComponent<RenderComponent>()->IsTextureFlipped() };

		float currentShootForce{ m_ShootForce };
		if (shootLeft)
		{
			currentShootForce *= -1.0f;
		}
		
		rigidBody->SetVelocity({ currentShootForce,20.0f});

	}

}

void dae::ShootBubbleCommand::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_pBubbleTexture = newTexture;
}
