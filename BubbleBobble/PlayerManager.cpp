#include "PlayerManager.h"
#include "Scene.h"
#include "EngineEvents.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerSpawnComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxCollision.h"
#include "MoveCommand.h"

void dae::PlayerManager::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(SceneLoaded))
	{
		if (payload.type() == typeid(Scene*))
		{
			// handle payload
			Scene* newlyLoadedScene{ std::any_cast<Scene*>(payload) };
			GameObject* sceneRoot{ newlyLoadedScene->GetRoot() };
			

			if (m_PlayerCount == 0)
			{
				// mark all players to be deleted
				for (GameObject* currPlayer : m_pPlayers)
				{
					currPlayer->MarkForDelete();
					currPlayer->SetParent(sceneRoot); // still move the object to scene root, this scene will handle its destruction
				}
				m_pPlayers.clear();

				return;
			}


			auto spawns{sceneRoot->GetComponentsInChildren<PlayerSpawnComponent>()};

			// if the players don't exist yet, create them
			if (m_pPlayers.empty())
			{
				CreatePlayers(sceneRoot);
			}

			// go through all players
			// make the player move to a different scene
			for (int index{0}; GameObject* currPlayer : m_pPlayers)
			{
				currPlayer->SetParent(sceneRoot);
				if (!spawns.empty())
				{
					glm::vec2 spawnPos{spawns[index]->GetSpawnPosition()};
					currPlayer->GetComponent<TransformComponent>()->SetLocalPosition(spawnPos.x, spawnPos.y);
				}
				currPlayer->GetComponent<RigidBody>()->SetVelocity({ 0.0f, 0.0f });
				++index;
			}

		}
	}
}

void dae::PlayerManager::CreatePlayers(GameObject* pRoot)
{
	if (m_PlayerCount > m_PlayerInfo.size())
		return;

	int controllerUsers{ 0 };
	for (unsigned int i = 0; i < m_PlayerCount; i++)
	{
		const PlayerInfo& currPlayerInfo{ m_PlayerInfo[i] };

		// create the player
		GameObject* player = new GameObject();
		player->SetParent(pRoot);
		auto renderComp = player->AddComponent<RenderComponent>();
		auto textureComp = player->AddComponent<dae::TextureComponent>();
		textureComp->SetTexture(currPlayerInfo.m_TexturePath);
		textureComp->AddToRenderer(renderComp);
		auto collisionComp = player->AddComponent<BoxCollision>();
		collisionComp->SetSize(currPlayerInfo.m_CollisionSizeX, currPlayerInfo.m_CollisionSizeY);
		renderComp->AddToDebug(collisionComp);
		player->AddComponent<RigidBody>();

		// cache the player here
		m_pPlayers.emplace_back(player);

		// do movement of player
		if (currPlayerInfo.m_UseKeyboard)
		{
			auto keyboardMoveCommand{ std::make_unique<MoveCommand>(
				player, 
				currPlayerInfo.m_BaseSpeed, 
				currPlayerInfo.m_BaseJumpStrength, 
				currPlayerInfo.m_JumpSoundId, 
				currPlayerInfo.m_JumpSoundPath) };
			InputManager::GetInstance().BindCommand(
				currPlayerInfo.m_KeyBoardInputs,
				currPlayerInfo.m_KeyboardInputType, 
				std::move(keyboardMoveCommand));

		}

		if (currPlayerInfo.m_UseController)
		{
			auto keyboardMoveCommand{ std::make_unique<MoveCommand>(
				player,
				currPlayerInfo.m_BaseSpeed,
				currPlayerInfo.m_BaseJumpStrength,
				currPlayerInfo.m_JumpSoundId,
				currPlayerInfo.m_JumpSoundPath) };
			InputManager::GetInstance().BindCommand(
				currPlayerInfo.m_ControllerInputs,
				currPlayerInfo.m_ControllerInputType,
				std::move(keyboardMoveCommand), controllerUsers);

			++controllerUsers; 
			// keep track of the controller users
			// probably won't need it, but if we have e.g. 4 players and the first and last player use controller
			// using the i will skip controller id 1 and 2, so if only 2 controllers are connected controller with id 3 will never be found
		}

	}
}
