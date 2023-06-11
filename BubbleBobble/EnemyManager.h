#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "GameObject.h"
#include "GameEvents.h"

namespace dae
{
	class Scene;
	class EnemyManager final : public Singleton<EnemyManager>, public Observer
	{
	public:
		void Notify(const Event& currEvent, std::any payload = nullptr) override;

	private:
		void CreateEnemies(GameObject* pRoot);
		std::vector<GameObject*> m_pEnemies{};
		size_t m_AmountOfEnemies{ 0 };
	};
}
