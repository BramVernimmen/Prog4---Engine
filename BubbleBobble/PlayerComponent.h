#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "Subject.h"
#include "GameEvents.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerState.h"


namespace dae
{
	class LivesComponent;
	class ScoreComponent;
	class PlayerState;
	class Texture2D;
	class PlayerComponent final : public UpdateComponent, public Subject, public Observer
	{
	public:
		PlayerComponent(GameObject* pOwner);
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;


		virtual void Update() override;

		void SetPlayerId(size_t newId) { m_PlayerId = newId; }
		size_t GetPlayerId() { return m_PlayerId; }

		virtual void Notify(const Event& currEvent, std::any payload = nullptr) override;

		void SetPlayerFalling();
		void SetPlayerRunning();
		void SetPlayerJumping();


		void SetJumpingSoundId(unsigned short id);
		void SetMovementSpeed(float newSpeed);
		void SetJumpingStrength(float newJump);
		void SetIdleTexture(std::shared_ptr<Texture2D> newTexture);

		PlayerState* GetCurrentState() { return m_pCurrentState; }

	private:
		size_t m_PlayerId{};
		std::unique_ptr<PlayerFallingState> m_pPlayerFallingState{std::make_unique<PlayerFallingState>(GetOwner())};
		std::unique_ptr<PlayerJumpingState> m_pPlayerJumpingState{std::make_unique<PlayerJumpingState>(GetOwner())};
		std::unique_ptr<PlayerRunningState> m_pPlayerRunningState{std::make_unique<PlayerRunningState>(GetOwner())};

		PlayerState* m_pCurrentState{};
	};

}

