#pragma once
#include "EnemyState.h"

namespace dae
{
	class GameObject;
	class RigidBody;
	class BoxCollision;
	class TransformComponent;
	class EnemyJumpingState final : public EnemyState
	{
	public:
		EnemyJumpingState(GameObject* pEnemy);
		~EnemyJumpingState() = default;

		EnemyJumpingState(const EnemyJumpingState& other) = delete;
		EnemyJumpingState(EnemyJumpingState&& other) = delete;
		EnemyJumpingState& operator=(const EnemyJumpingState& other) = delete;
		EnemyJumpingState& operator=(EnemyJumpingState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override;

	private:
		RigidBody* m_pRigidBody{nullptr};
		TransformComponent* m_pTransformComp{};
		BoxCollision* m_pBoxCollision{};

		float m_TopPosY{};
		float m_BottomPosY{};
		int m_GridPixelSize{};

		float m_MaxTopPosY{};
		float m_MaxBottomPosY{};
	};

}

