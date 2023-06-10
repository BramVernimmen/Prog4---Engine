#pragma once
#include "UpdateComponent.h"
#include "Subject.h"

namespace dae
{

	class LivesComponent final : public UpdateComponent, public Subject
	{
	public:
		LivesComponent(GameObject* pOwner);
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;


		virtual void Update() override {};

		void SetMaxLives(int newMax) { m_MaxLives = newMax; }
		void ResetLives();
		int GetCurrentLives() { return m_CurrentLives; }
		void RemoveLife();

	private:
		int m_CurrentLives{};
		int m_MaxLives{5};


	};

}
