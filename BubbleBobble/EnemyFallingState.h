#pragma once
#include "EnemyState.h"

namespace dae
{
	class GameObject;
	class RigidBody;
	class TransformComponent;
	class EnemyFallingState final : public EnemyState
	{
	public:
		EnemyFallingState(GameObject* pEnemy);
		~EnemyFallingState() = default;

		EnemyFallingState(const EnemyFallingState& other) = delete;
		EnemyFallingState(EnemyFallingState&& other) = delete;
		EnemyFallingState& operator=(const EnemyFallingState& other) = delete;
		EnemyFallingState& operator=(EnemyFallingState&& other) = delete;

		virtual void OnEnter() override {}
		virtual void Update() override;
		virtual void OnExit() override {}

	private:
		RigidBody* m_pRigidBody{};
		TransformComponent* m_pTransformComp{};
		float m_TopPosY{};
		float m_BottomPosY{};
		int m_GridPixelSize{};

		float m_MaxTopPosY{};
		float m_MaxBottomPosY{};
	};

}
