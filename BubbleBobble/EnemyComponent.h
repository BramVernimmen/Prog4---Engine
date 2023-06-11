#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "Subject.h"
#include "GameEvents.h"
#include "EnemyFallingState.h"
#include "EnemyJumpingState.h"
#include "EnemyRunningState.h"
#include "EnemyDeathState.h"
#include "EnemyBubbleState.h"
#include "EnemyState.h"


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

		void SetEnemyFalling();
		void SetEnemyRunning();
		void SetEnemyJumping();
		void SetEnemyBubble();
		void SetEnemyDeath();
		

		void SetMovementSpeed(float newSpeed);
		void SetJumpingStrength(float newJump);
		void SetIdleTexture(std::shared_ptr<Texture2D> newTexture);
		void SetBubbleTexture(std::shared_ptr<Texture2D> newTexture);
		void SetDeathTexture(std::shared_ptr<Texture2D> newTexture);

		EnemyState* GetCurrentState() { return m_pCurrentState; }

		int GetValue() { return m_Value; }
	private:
		std::unique_ptr<EnemyFallingState> m_pEnemyFallingState{std::make_unique<EnemyFallingState>(GetOwner())};
		std::unique_ptr<EnemyJumpingState> m_pEnemyJumpingState{std::make_unique<EnemyJumpingState>(GetOwner())};
		std::unique_ptr<EnemyRunningState> m_pEnemyRunningState{std::make_unique<EnemyRunningState>(GetOwner())};
		std::unique_ptr<EnemyBubbleState> m_pEnemyBubbleState{std::make_unique<EnemyBubbleState>(GetOwner())};
		std::unique_ptr<EnemyDeathState> m_pEnemyDeathState{std::make_unique<EnemyDeathState>(GetOwner())};

		EnemyState* m_pCurrentState{};

		int m_Value{1000};
	};

}

