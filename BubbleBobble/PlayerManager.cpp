#include "PlayerManager.h"
#include "Scene.h"
#include "EngineEvents.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerSpawnComponent.h"
#include "TransformComponent.h"

void dae::PlayerManager::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(SceneLoaded))
	{
		if (payload.type() == typeid(Scene*))
		{
			// handle payload
			Scene* newlyLoadedScene{ std::any_cast<Scene*>(payload) };
			GameObject* sceneRoot{ newlyLoadedScene->GetRoot() };
			

			auto spawns{sceneRoot->GetComponentsInChildren<PlayerSpawnComponent>()};

			// if the players don't exist yet, create them
			//if (m_pPlayers.empty())
			//{
			//	CreatePlayers(sceneRoot);
			//}

			// go through all players
			// make the player move to a different scene
			if (m_pPlayer)
			{
				m_pPlayer->SetParent(sceneRoot);
				if (!spawns.empty())
				{
					glm::vec2 spawnPos{spawns[0]->GetSpawnPosition()};
					m_pPlayer->GetComponent<TransformComponent>()->SetLocalPosition(spawnPos.x, spawnPos.y);
				}

				m_pPlayer->GetComponent<RigidBody>()->SetVelocity({ 0.0f, 0.0f });
			}
		}
	}
}

void dae::PlayerManager::CreatePlayers(GameObject* pRoot)
{
	pRoot;
}
