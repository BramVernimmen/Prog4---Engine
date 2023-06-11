#include "EnemyManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EnemySpawnComponent.h"
#include "RigidBody.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxCollision.h"
#include "EnemyComponent.h"
#include "ResourceManager.h"

void dae::EnemyManager::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(SceneLoaded))
	{
		if (payload.type() == typeid(Scene*))
		{
			// handle payload
			// first check if we have enemies, if we do, destroy all of them
			if (!m_pEnemies.empty())
			{
				for (GameObject* currEnemy : m_pEnemies)
				{
					currEnemy->MarkForDelete();
				}

				m_pEnemies.clear();
				m_AmountOfEnemies = 0;
			}

			Scene* newlyLoadedScene{ std::any_cast<Scene*>(payload) };
			GameObject* sceneRoot{ newlyLoadedScene->GetRoot() };

			auto spawns{ sceneRoot->GetComponentsInChildren<EnemySpawnComponent>() };
			m_AmountOfEnemies = spawns.size();
			if (m_AmountOfEnemies == 0)
				return;

			CreateEnemies(sceneRoot);

			for (int index{ 0 }; GameObject * currEnemy : m_pEnemies)
			{
				currEnemy->SetParent(sceneRoot);
				if (!spawns.empty())
				{
					glm::vec2 spawnPos{spawns[index]->GetSpawnPosition()};
					currEnemy->GetComponent<TransformComponent>()->SetLocalPosition(spawnPos.x, spawnPos.y);
				}
				++index;
			}

		}
	}

}

void dae::EnemyManager::CreateEnemies(GameObject* pRoot)
{
	for (size_t i = 0; i < m_AmountOfEnemies; ++i)
	{
		GameObject* enemy = new GameObject();
		enemy->SetParent(pRoot);
		auto renderComp = enemy->AddComponent<RenderComponent>();
		auto textureComp = enemy->AddComponent<dae::TextureComponent>();
		textureComp->AddToRenderer(renderComp);
		enemy->AddComponent<RigidBody>();
		auto collisionComp = enemy->AddComponent<BoxCollision>();
		collisionComp->SetCurrentLayer(0b100);
		collisionComp->SetSize(35, 48);
		renderComp->AddToDebug(collisionComp);
		auto enemyComp = enemy->AddComponent<EnemyComponent>();
		enemyComp->SetIdleTexture(ResourceManager::GetInstance().LoadTexture("ZenChan/Run.png"));
		enemyComp->SetMovementSpeed(100.0f);
		enemyComp->SetJumpingStrength(250.0f);
		enemyComp->SetDeathTexture(ResourceManager::GetInstance().LoadTexture("ZenChan/Death.png"));
		enemyComp->SetBubbleTexture(ResourceManager::GetInstance().LoadTexture("ZenChan/InBubble.png"));

		enemyComp->SetEnemyBubble();


		m_pEnemies.emplace_back(enemy);

	}
}
