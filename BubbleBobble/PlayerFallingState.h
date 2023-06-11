#pragma once
#include "PlayerState.h"

namespace dae
{
	class GameObject;
	class RigidBody;
	class BoxCollision;
	class RenderComponent;
	class PlayerFallingState final : public PlayerState
	{
	public:
		PlayerFallingState(GameObject* pPlayer);
		~PlayerFallingState() = default;

		PlayerFallingState(const PlayerFallingState& other) = delete;
		PlayerFallingState(PlayerFallingState&& other) = delete;
		PlayerFallingState& operator=(const PlayerFallingState& other) = delete;
		PlayerFallingState& operator=(PlayerFallingState&& other) = delete;

		virtual void OnEnter() override {}
		virtual void Update() override;
		virtual void OnExit() override {}
		virtual void HandleInput(std::any payload) override;

	private:
		RigidBody* m_pRigidBody{};
		RenderComponent* m_pRenderComp{};

	};

}