#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "GameEvents.h"

namespace dae
{
	class RigidBody;
	class BubbleComponent final : public UpdateComponent, public Observer
	{
	public:
		BubbleComponent(GameObject* pOwner);
		~BubbleComponent() = default;
		BubbleComponent(const BubbleComponent& other) = delete;
		BubbleComponent(BubbleComponent&& other) = delete;
		BubbleComponent& operator=(const BubbleComponent& other) = delete;
		BubbleComponent& operator=(BubbleComponent&& other) = delete;


		virtual void Update() override;


		virtual void Notify(const Event& currEvent, std::any payload = nullptr) override;

	private:
		float m_CurrentTimeAlive{0.0f};
		float m_MaxLifeTime{ 1.0f };
		RigidBody* m_pRigidBody{ };
	};

}

