#pragma once
#include "PlayerState.h"

namespace dae
{
	class GameObject;
	class RigidBody;
	class BoxCollision;
	class RenderComponent;
	class PlayerJumpingState final : public PlayerState
	{
	public:
		PlayerJumpingState(GameObject* pPlayer);
		~PlayerJumpingState() = default;

		PlayerJumpingState(const PlayerJumpingState& other) = delete;
		PlayerJumpingState(PlayerJumpingState&& other) = delete;
		PlayerJumpingState& operator=(const PlayerJumpingState& other) = delete;
		PlayerJumpingState& operator=(PlayerJumpingState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;
		virtual void HandleInput(std::any payload) override;

		void SetJumpSoundId(unsigned short id) { m_JumpSoundId = id; }

	private:
		unsigned short m_JumpSoundId{};
		RigidBody* m_pRigidBody{};
		BoxCollision* m_pBoxCollision{};
		RenderComponent* m_pRenderComp{};

	};

}

