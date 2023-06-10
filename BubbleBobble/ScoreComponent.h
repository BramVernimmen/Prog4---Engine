#pragma once
#include "UpdateComponent.h"
#include "Subject.h"
#include "Observer.h"
#include "GameEvents.h"

namespace dae
{

	class ScoreComponent final : public UpdateComponent, public Subject, public Observer
	{
	public:
		ScoreComponent(GameObject* pOwner);
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;


		virtual void Update() override {};

		int GetCurrentScore() { return m_CurrentScore; }
		void AddScore(int scoreToAdd);

		virtual void Notify(const Event& currEvent, std::any payload = nullptr) override;

	private:
		int m_CurrentScore{ 0 };
	};

}
