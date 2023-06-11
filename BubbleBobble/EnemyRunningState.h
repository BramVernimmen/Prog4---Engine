#pragma once
#include "EnemyState.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class GameObject;
	class RenderComponent;
	class RigidBody;
	class EnemyRunningState final : public EnemyState
	{
	public:
		EnemyRunningState(GameObject* pEnemy);
		~EnemyRunningState() = default;

		EnemyRunningState(const EnemyRunningState& other) = delete;
		EnemyRunningState(EnemyRunningState&& other) = delete;
		EnemyRunningState& operator=(const EnemyRunningState& other) = delete;
		EnemyRunningState& operator=(EnemyRunningState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override {}

		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		void SetMovementSpeed(float newSpeed) { m_MovementSpeed = newSpeed; }
		void SetJumpStrength(float newJumpForce) { m_JumpStrength = newJumpForce; }

	private:
		std::shared_ptr<Texture2D> m_pRunningTexture{};
		RenderComponent* m_pRenderComp{};
		RigidBody* m_pRigidBody{};
		float m_MovementSpeed{};
		float m_JumpStrength{};
	};

}
