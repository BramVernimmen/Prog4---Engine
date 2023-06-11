#pragma once
#include "PlayerState.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class GameObject;
	class RenderComponent;
	class PlayerDeathState final : public PlayerState
	{
	public:
		PlayerDeathState(GameObject* pPlayer);
		~PlayerDeathState() = default;

		PlayerDeathState(const PlayerDeathState& other) = delete;
		PlayerDeathState(PlayerDeathState&& other) = delete;
		PlayerDeathState& operator=(const PlayerDeathState& other) = delete;
		PlayerDeathState& operator=(PlayerDeathState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override {};
		virtual void OnExit() override {}
		virtual void HandleInput(std::any payload) override {};

		void SetTexture(std::shared_ptr<Texture2D> newTexture);

	private:
		std::shared_ptr<Texture2D> m_pDeathTexture{};
		RenderComponent* m_pRenderComp{};
	};

}

