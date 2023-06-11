#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "Subject.h"
#include "GameEvents.h"
//#include "PlayerFallingState.h"
//#include "PlayerJumpingState.h"
//#include "PlayerRunningState.h"
//#include "PlayerDeathState.h"
//#include "PlayerState.h"


namespace dae
{
	class Texture2D;
	class EnemyComponent final : public UpdateComponent, public Subject
	{
	public:
		EnemyComponent(GameObject* pOwner);
		~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;


		virtual void Update() override;

		//void SetPlayerFalling();
		//void SetPlayerRunning();
		//void SetPlayerJumping();
		//void SetPlayerDeath();
		//
		//void SetJumpingSoundId(unsigned short id);
		//void SetMovementSpeed(float newSpeed);
		//void SetJumpingStrength(float newJump);
		//void SetIdleTexture(std::shared_ptr<Texture2D> newTexture);
		//void SetDeathTexture(std::shared_ptr<Texture2D> newTexture);

		//PlayerState* GetCurrentState() { return m_pCurrentState; }

	private:
		//std::unique_ptr<PlayerFallingState> m_pPlayerFallingState{std::make_unique<PlayerFallingState>(GetOwner())};
		//std::unique_ptr<PlayerJumpingState> m_pPlayerJumpingState{std::make_unique<PlayerJumpingState>(GetOwner())};
		//std::unique_ptr<PlayerRunningState> m_pPlayerRunningState{std::make_unique<PlayerRunningState>(GetOwner())};
		//std::unique_ptr<PlayerDeathState> m_pPlayerDeathState{std::make_unique<PlayerDeathState>(GetOwner())};

		//PlayerState* m_pCurrentState{};
	};

}

