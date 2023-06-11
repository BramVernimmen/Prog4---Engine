#pragma once
#include "EnemyState.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class GameObject;
	class RenderComponent;
	class TransformComponent;
	class BoxCollision;
	class EnemyBubbleState final : public EnemyState
	{
	public:
		EnemyBubbleState(GameObject* pEnemy);
		~EnemyBubbleState() = default;

		EnemyBubbleState(const EnemyBubbleState& other) = delete;
		EnemyBubbleState(EnemyBubbleState&& other) = delete;
		EnemyBubbleState& operator=(const EnemyBubbleState& other) = delete;
		EnemyBubbleState& operator=(EnemyBubbleState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override;
		virtual void OnExit() override {}

		void SetTexture(std::shared_ptr<Texture2D> newTexture);

	private:
		std::shared_ptr<Texture2D> m_pBubbleTexture{};
		RenderComponent* m_pRenderComp{};
		TransformComponent* m_pTransformComp{};
		BoxCollision* m_pBoxCollision{};
		float m_TopPosY{};
		int m_GridPixelSize{};
		float m_MaxTopPosY{};

		float m_MaxDuration{ 3.5f };
		float m_CurrentDuration{ 0.0f };
	};

}

