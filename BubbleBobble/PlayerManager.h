#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "GameObject.h"

namespace dae
{
	class Scene;
	class PlayerManager final : public Singleton<PlayerManager>, public Observer
	{
	public:

		void SetPlayer(GameObject* pPlayer) { m_pPlayer = pPlayer; }
		void SetPlayerCount(int playerCount) { m_PlayerCount = playerCount; }

		void Notify(const Event& currEvent, std::any payload = nullptr) override;

	private:
		void CreatePlayers(GameObject* pRoot);
		std::vector<GameObject*> m_pPlayers{};
		GameObject* m_pPlayer{};

		int m_PlayerCount{ 1 };
	};
}
