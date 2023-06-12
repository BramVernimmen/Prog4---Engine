#pragma once
#include "PlayerState.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class GameObject;
	class RenderComponent;
	class RigidBody;
	class PlayerRunningState final : public PlayerState
	{
	public:
		PlayerRunningState(GameObject* pPlayer);
		~PlayerRunningState() = default;
	
		PlayerRunningState(const PlayerRunningState& other) = delete;
		PlayerRunningState(PlayerRunningState&& other) = delete;
		PlayerRunningState& operator=(const PlayerRunningState& other) = delete;
		PlayerRunningState& operator=(PlayerRunningState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
		virtual void HandleInput(std::any payload) override;

		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		void SetMovementSpeed(float newSpeed) { m_MovementSpeed = newSpeed; }
		void SetJumpStrength(float newJumpForce) { m_JumpStrength = newJumpForce; }

		bool CanShoot() { return m_CanShoot; }
		void Shoot() { m_CanShoot = false; }

	private:
		std::shared_ptr<Texture2D> m_pRunningTexture{};
		RenderComponent* m_pRenderComp{};
		RigidBody* m_pRigidBody{};
		float m_MovementSpeed{};
		float m_JumpStrength{};

		bool m_CanShoot{ true };
		float m_MaxShootTimer{ 0.5f };
		float m_CurrentShootTimer{ 0.0f };
	};

}
