#include "PlayerManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EngineEvents.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerSpawnComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "BoxCollision.h"
#include "MoveCommand.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "DebugLivesComponent.h"
#include "DebugScoreComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
#include <iostream>
#include "ServiceLocator.h"
#include "SoundSystem.h"

void dae::PlayerManager::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(SceneLoaded))
	{
		if (payload.type() == typeid(Scene*))
		{
			// handle payload
			Scene* newlyLoadedScene{ std::any_cast<Scene*>(payload) };
			if (newlyLoadedScene->GetName().find("Level_") == std::string::npos)
			{
				// if we get here, a scene was loaded that wasn't a level
				// for now just destroy the players if this happens
				SetPlayerCount(0);
			}
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

				// also remove all player commands
				for (auto& currPlayerCommands : m_pPlayerCommands)
				{
					for (Command* currCommand : currPlayerCommands)
					{
						InputManager::GetInstance().RemoveCommand(currCommand);
					}
				}
				m_pPlayerCommands.clear();

				for (auto& currPlayerDebugs : m_pPlayerDebugs)
				{
					for (GameObject* currDebug : currPlayerDebugs)
					{
						currDebug->MarkForDelete();
					}
				}
				m_pPlayerDebugs.clear();

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

			for (auto& currPlayerDebugs : m_pPlayerDebugs)
			{
				for (GameObject* currDebug : currPlayerDebugs)
				{
					currDebug->SetParent(sceneRoot);
				}
			}

		}
	}
}

void dae::PlayerManager::RespawnPlayer(GameObject* pOwner, size_t playerId)
{
	// issue with respawning
	auto spawns{ SceneManager::GetInstance().GetActiveScene()->GetRoot()->GetComponentsInChildren<PlayerSpawnComponent>()};
	glm::vec2 spawnPos{spawns[playerId]->GetSpawnPosition()};
	pOwner->GetComponent<TransformComponent>()->SetLocalPosition(spawnPos.x, spawnPos.y);
	pOwner->GetComponent<RigidBody>()->SetVelocity({ 0.0f, 0.0f });
}

void dae::PlayerManager::CreatePlayers(GameObject* pRoot)
{
	if (m_PlayerCount > m_PlayerInfo.size())
		return;

	int controllerUsers{ 0 };
	std::vector<Command*> playerCommands{};

	for (unsigned int i = 0; i < m_PlayerCount; i++)
	{
		const PlayerInfo& currPlayerInfo{ m_PlayerInfo[i] };

		// create the player
		GameObject* player = new GameObject();
		player->SetParent(pRoot);
		auto renderComp = player->AddComponent<RenderComponent>();
		auto textureComp = player->AddComponent<dae::TextureComponent>();
		//textureComp->SetTexture(currPlayerInfo.m_TexturePath);
		textureComp->AddToRenderer(renderComp);
		player->AddComponent<RigidBody>();
		auto livesComp = player->AddComponent<LivesComponent>();
		auto scoreComp = player->AddComponent<ScoreComponent>();
		// player comp uses lives and score, make sure it's created after those
		auto collisionComp = player->AddComponent<BoxCollision>();
		collisionComp->SetCurrentLayer(0b1100);
		collisionComp->AddLayerForOverlapEvent(0b1100);
		collisionComp->SetSize(currPlayerInfo.m_CollisionSizeX, currPlayerInfo.m_CollisionSizeY);
		renderComp->AddToDebug(collisionComp);
		auto playerComp = player->AddComponent<PlayerComponent>();
		playerComp->SetPlayerId(static_cast<size_t>(i));
		playerComp->AddObserver(livesComp);
		livesComp->AddObserver(playerComp);
		playerComp->AddObserver(scoreComp);
		collisionComp->AddObserver(playerComp);
		

		auto& ss{ ServiceLocator::GetSoundSystem() }; 
		ss.Load(currPlayerInfo.m_JumpSoundId, currPlayerInfo.m_JumpSoundPath);

		playerComp->SetJumpingSoundId(currPlayerInfo.m_JumpSoundId);
		playerComp->SetMovementSpeed(currPlayerInfo.m_BaseSpeed);
		playerComp->SetJumpingStrength(currPlayerInfo.m_BaseJumpStrength);
		std::string texturePath{currPlayerInfo.m_TexturePath};
		playerComp->SetIdleTexture(ResourceManager::GetInstance().LoadTexture(texturePath + "/Idle.png"));
		playerComp->SetDeathTexture(ResourceManager::GetInstance().LoadTexture(texturePath + "/Death.png"));




		// cache the player here
		m_pPlayers.emplace_back(player);

		// do movement of player
		if (currPlayerInfo.m_UseKeyboard)
		{
			auto keyboardMoveCommand{ std::make_unique<MoveCommand>(player) };

			playerCommands.emplace_back(keyboardMoveCommand.get());

			InputManager::GetInstance().BindCommand(
				currPlayerInfo.m_KeyBoardInputs,
				currPlayerInfo.m_KeyboardInputType, 
				std::move(keyboardMoveCommand));

		}

		if (currPlayerInfo.m_UseController)
		{
			auto controllerMoveCommand{ std::make_unique<MoveCommand>(player) };

			playerCommands.emplace_back(controllerMoveCommand.get());

			InputManager::GetInstance().BindCommand(
				currPlayerInfo.m_ControllerInputs,
				currPlayerInfo.m_ControllerInputType,
				std::move(controllerMoveCommand), controllerUsers);

			++controllerUsers; 
			// keep track of the controller users
			// probably won't need it, but if we have e.g. 4 players and the first and last player use controller
			// using the i will skip controller id 1 and 2, so if only 2 controllers are connected controller with id 3 will never be found
		}
		m_pPlayerCommands.emplace_back(playerCommands);


		// create the lives and score display of the players
		std::vector<GameObject*> playerDebugs{};
		// starting with the lives display
		GameObject* debugLivesObj = new GameObject();
		debugLivesObj->SetParent(pRoot);
		auto transComp = debugLivesObj->GetComponent<TransformComponent>();
		transComp->SetLocalPosition(currPlayerInfo.m_DisplayTopLeftX, currPlayerInfo.m_DisplayTopLeftY);
		renderComp = debugLivesObj->AddComponent<RenderComponent>();
		auto textComp = debugLivesObj->AddComponent<TextComponent>();
		auto font = ResourceManager::GetInstance().LoadFont(currPlayerInfo.m_FontPath, currPlayerInfo.m_FontSize);
		textComp->SetFont(font);
		textComp->SetColor({currPlayerInfo.m_FontColorR, currPlayerInfo.m_FontColorG, currPlayerInfo.m_FontColorB });
		textComp->AddToRenderer(renderComp);
		auto debugLivesComp = debugLivesObj->AddComponent<DebugLivesComponent>();
		debugLivesComp->SetLastLives(livesComp->GetCurrentLives());
		// add as observer
		livesComp->AddObserver(debugLivesComp);
		playerDebugs.emplace_back(debugLivesObj);

		// next the display for the score
		GameObject* debugScoreObj = new GameObject();
		debugLivesObj->SetParent(pRoot);
		transComp = debugScoreObj->GetComponent<TransformComponent>();
		transComp->SetLocalPosition(currPlayerInfo.m_DisplayTopLeftX, currPlayerInfo.m_DisplayTopLeftY + currPlayerInfo.m_FontSize);
		renderComp = debugScoreObj->AddComponent<RenderComponent>();
		textComp = debugScoreObj->AddComponent<TextComponent>();
		font = ResourceManager::GetInstance().LoadFont(currPlayerInfo.m_FontPath, currPlayerInfo.m_FontSize);
		textComp->SetFont(font);
		textComp->SetColor({ currPlayerInfo.m_FontColorR, currPlayerInfo.m_FontColorG, currPlayerInfo.m_FontColorB });
		textComp->AddToRenderer(renderComp);
		auto debugScoreComp = debugScoreObj->AddComponent<DebugScoreComponent>();
		// add as observer
		scoreComp->AddObserver(debugScoreComp);
		playerDebugs.emplace_back(debugScoreObj);

		m_pPlayerDebugs.emplace_back(playerDebugs);
	}
}
