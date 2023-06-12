#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "HowToPlayComponent.h"
#include "ServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SdlSoundSystem.h"
#include "SkipLevelCommand.h"
#include "GoBackLevelCommand.h"
#include "LevelLoaderComponent.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "MainMenuComponent.h"
#include "EndMenuComponent.h"
#include "MuteCommand.h"

void load()
{

	auto mainMenuScene = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	dae::GameObject* pRootMainMenu = mainMenuScene->GetRoot();


	dae::ServiceLocator::SetSoundSystem(new dae::SdlSoundSystem());
	//dae::ServiceLocator::SetSoundSystem(new dae::LoggingSoundSystem(new dae::SdlSoundSystem));
	
	auto& ss{ dae::ServiceLocator::GetSoundSystem() };
	ss.LoadTrack(0, "Music/MainTheme.mp3");
	ss.LoadTrack(1, "Music/shoulder.mp3");
	ss.PlayTrack(0);

	// level loader
	dae::GameObject* levelLoader = new dae::GameObject();
	levelLoader->SetParent(pRootMainMenu);
	auto levelLoaderComp = levelLoader->AddComponent<dae::LevelLoaderComponent>();
	levelLoaderComp->AddLevelFile("Levels/001.txt");
	levelLoaderComp->AddLevelFile("Levels/002.txt");
	levelLoaderComp->AddLevelFile("Levels/003.txt");
	levelLoaderComp->AddLevelFile("Levels/004.txt");
	levelLoaderComp->AddLevelFile("Levels/005.txt");
	levelLoaderComp->SetTileTextureLocation("Tiles/");
	levelLoaderComp->SetTileTextureExtension("_Tile.png");
	levelLoaderComp->SetGridOffset(50, 60);
	levelLoaderComp->SetGridSize(32, 26);
	levelLoaderComp->CreateLevels();
	levelLoader->MarkForDelete(); // we don't need it after this, so we can already mark it



	dae::PlayerManager* playerManager{&dae::PlayerManager::GetInstance()};
	dae::EnemyManager* enemyManager{&dae::EnemyManager::GetInstance()};
	// add playerManager as Observer to every scene
	for (const auto& currScene : dae::SceneManager::GetInstance().GetScenes())
	{
		currScene->AddObserver(playerManager);
		currScene->AddObserver(enemyManager);
	}




	dae::PlayerInfo player1Info{};
	player1Info.m_TexturePath = "Bubby";
	player1Info.m_UseController = true;
	player1Info.m_DisplayTopLeftX = 150.0f;
	player1Info.m_FontColorR = 135;
	player1Info.m_FontColorG = 249;
	player1Info.m_FontColorB = 81;

	dae::PlayerInfo player2Info{};
	player2Info.m_TexturePath = "Bobby";
	player2Info.m_UseController = true;
	player2Info.m_KeyBoardInputs = { SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN }; // player 2 will use arrow keys
	player2Info.m_KeyBoardShootInput = { SDLK_KP_0 };
	player2Info.m_DisplayTopLeftX = 600.0f;
	player2Info.m_FontColorR = 73;
	player2Info.m_FontColorG = 169;
	player2Info.m_FontColorB = 250;

	playerManager->AddPlayerInfo(player1Info);
	playerManager->AddPlayerInfo(player2Info);




	// ==== Main Menu Stuff ========

	// fps - will be shown in the main menu
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	dae::GameObject* fps = new dae::GameObject();
	fps->SetParent(pRootMainMenu);
	auto renderComp = fps->AddComponent<dae::RenderComponent>();
	auto transComp = fps->GetComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0, 0);
	auto textComponent = fps->AddComponent<dae::TextComponent>();
	textComponent->SetFont(font);
	textComponent->SetText("FPS");
	textComponent->SetColor({ 150, 150, 0 });
	textComponent->AddToRenderer(renderComp);
	fps->AddComponent<dae::FPSComponent>();


	// =========== How To Play? ========
	dae::GameObject* howToPlay = new dae::GameObject();
	howToPlay->SetParent(pRootMainMenu);
	renderComp = howToPlay->AddComponent<dae::RenderComponent>();
	auto tutorialComp = howToPlay->AddComponent<dae::HowToPlayComponent>();
	renderComp->AddToDisplayGui(tutorialComp);

	dae::GameObject* mainMenuObj = new dae::GameObject();
	mainMenuObj->SetParent(pRootMainMenu);
	renderComp = mainMenuObj->AddComponent<dae::RenderComponent>();
	auto mainMenuComp = mainMenuObj->AddComponent<dae::MainMenuComponent>();
	renderComp->AddToDisplayGui(mainMenuComp);




	// =======================================================


	// ==== End Menu Stuff ========

	// after all levels have been created; create end menu
	auto endMenuScene = dae::SceneManager::GetInstance().CreateScene("EndMenu");
	dae::GameObject* pRootEndMenu = endMenuScene->GetRoot();


	dae::GameObject* endMenuObj = new dae::GameObject();
	endMenuObj->SetParent(pRootEndMenu);
	renderComp = endMenuObj->AddComponent<dae::RenderComponent>();
	auto endMenuComp = endMenuObj->AddComponent<dae::EndMenuComponent>();
	renderComp->AddToDisplayGui(endMenuComp);
	endMenuComp->SetHighScoreFilePath("Highscore.txt");

	// =======================================================




	// =========== Skip/GoBack Level Buttons ========
	auto skipLevelCommand{ std::make_unique<dae::SkipLevelCommand>() };
	dae::InputManager::GetInstance().BindCommand({ SDLK_F4 }, dae::InputManager::InputType::OnButtonDown, std::move(skipLevelCommand));

	auto prevLevelCommand{ std::make_unique<dae::GoBackLevelCommand>() };
	dae::InputManager::GetInstance().BindCommand({ SDLK_F3 }, dae::InputManager::InputType::OnButtonDown, std::move(prevLevelCommand));

	auto muteCommand{ std::make_unique<dae::MuteCommand>() };
	dae::InputManager::GetInstance().BindCommand({SDLK_F5}, dae::InputManager::InputType::OnButtonDown, std::move(muteCommand));

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}