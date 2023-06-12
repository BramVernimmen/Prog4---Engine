#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "GameEvents.h"

namespace dae
{
	class Scene;
	class GameManager final : public Singleton<GameManager>, public Observer
	{
	public:
		void Notify(const Event& currEvent, std::any payload = nullptr) override;

		void AllPlayersDead();
		void AllEnemiesDead();

		void SetHighscore(int newScore) { m_CurrentMaxScore = newScore; }

		void SetEndScene(Scene* pEndScene) { m_pEndScene = pEndScene; }
	private:
		int m_CurrentMaxScore{ 0 };
		Scene* m_pEndScene{};

	};
}
