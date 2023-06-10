//#include <SDL.h>

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
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
//#include "HealthComponent.h"
//#include "DebugHealthComponent.h"
#include "DamageCommand.h"
#include "ScoreComponent.h"
#include "DebugScoreComponent.h"
#include "GiveScoreCommand.h"
#include "HowToPlayComponent.h"
#include "GridComponent.h"
#include "BoxCollision.h"
#include "RigidBody.h"
#include "ServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SdlSoundSystem.h"
#include "SkipLevelCommand.h"
#include "GoBackLevelCommand.h"
#include "LevelLoaderComponent.h"
#include "PlayerManager.h"

void load()
{

	auto scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");
	auto testScene = dae::SceneManager::GetInstance().CreateScene("TEST");
	dae::GameObject* pRootDemo = scene->GetRoot();

	dae::SceneManager::GetInstance().RemoveScene(testScene);
	dae::SceneManager::GetInstance().AddScene(testScene);


	dae::ServiceLocator::SetSoundSystem(new dae::SdlSoundSystem());
	//dae::ServiceLocator::SetSoundSystem(new dae::LoggingSoundSystem(new dae::SdlSoundSystem));
	//auto& ss = dae::ServiceLocator::GetSoundSystem();

	//ss.Load(0, "Sounds/Pickup.wav");
	//ss.Play(0);

	// level loader
	dae::GameObject* levelLoader = new dae::GameObject();
	levelLoader->SetParent(pRootDemo);
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


	dae::PlayerManager* playerManager{&dae::PlayerManager::GetInstance()};
	// add playerManager as Observer to every scene
	for (const auto& currScene : dae::SceneManager::GetInstance().GetScenes())
	{
		currScene->AddObserver(playerManager);
	}


	// fps - will be shown in the main menu
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	dae::GameObject* fps = new dae::GameObject();
	fps->SetParent(pRootDemo);
	auto renderComp = fps->AddComponent<dae::RenderComponent>();
	auto transComp = fps->GetComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0, 0);
	auto textComponent = fps->AddComponent<dae::TextComponent>();
	textComponent->SetFont(font);
	textComponent->SetText("FPS");
	textComponent->SetColor({ 150, 150, 0 });
	textComponent->AddToRenderer(renderComp);
	fps->AddComponent<dae::FPSComponent>();




	dae::PlayerInfo player1Info{};
	player1Info.m_TexturePath = "Bubby.png";
	player1Info.m_UseController = true;
	player1Info.m_DisplayTopLeftX = 150.0f;
	player1Info.m_FontColorR = 135;
	player1Info.m_FontColorG = 249;
	player1Info.m_FontColorB = 81;

	dae::PlayerInfo player2Info{};
	player2Info.m_TexturePath = "Bobby.png";
	player2Info.m_UseController = true;
	player2Info.m_KeyBoardInputs = { SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_RIGHT }; // player 2 will use arrow keys
	player2Info.m_DisplayTopLeftX = 600.0f;
	player2Info.m_FontColorR = 73;
	player2Info.m_FontColorG = 169;
	player2Info.m_FontColorB = 250;

	playerManager->AddPlayerInfo(player1Info);
	playerManager->AddPlayerInfo(player2Info);

	//dae::SceneManager::GetInstance().PreviousScene();
	//playerManager->SetPlayerCount(0);

	// bubby - has lives + score (P1)
	//dae::GameObject* bubby = new dae::GameObject();
	//bubby->SetParent(pRootDemo);
	//renderComp = bubby->AddComponent<dae::RenderComponent>();
	//transComp = bubby->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(220.0f, 210.0f);
	//auto textureComp = bubby->AddComponent<dae::TextureComponent>();
	//textureComp->SetTexture("Bubby.png");
	//textureComp->AddToRenderer(renderComp);
	////auto healthComp = bubby->AddComponent<dae::HealthComponent>();
	////auto scoreComp = bubby->AddComponent<dae::ScoreComponent>();
	////healthComp->AddObserver(scoreComp); // our score needs to listen to our own health (for this test)
	//auto collision = bubby->AddComponent<dae::BoxCollision>();
	//collision->SetSize(48, 48);
	//renderComp->AddToDebug(collision);

	//bubby->AddComponent<dae::RigidBody>();


	//// P1 health debug
	//dae::GameObject* debugHealthP1 = new dae::GameObject();
	//debugHealthP1->SetParent(pRootDemo);
	//renderComp = debugHealthP1->AddComponent<dae::RenderComponent>();
	//transComp = debugHealthP1->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(0.0f, 150.0f);
	//textComponent = debugHealthP1->AddComponent<dae::TextComponent>();
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	//textComponent->SetFont(font);
	//textComponent->SetColor({ 0, 255, 0 });
	//textComponent->AddToRenderer(renderComp);
	//auto debugHealthComp = debugHealthP1->AddComponent<dae::DebugHealthComponent>();
	//debugHealthComp->SetLastHealth(healthComp->GetCurrentHealth());

	//// P1 score debug
	//dae::GameObject* debugScoreP1 = new dae::GameObject();
	//debugScoreP1->SetParent(pRootDemo);
	//renderComp = debugScoreP1->AddComponent<dae::RenderComponent>();
	//transComp = debugScoreP1->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(0.0f, 170.f);
	//textComponent = debugScoreP1->AddComponent<dae::TextComponent>();
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	//textComponent->SetFont(font);
	//textComponent->SetColor({ 0, 255, 0 });
	//textComponent->AddToRenderer(renderComp);
	//auto debugScoreComp = debugScoreP1->AddComponent<dae::DebugScoreComponent>();

	//// add	debug observer to bubby
	//healthComp->AddObserver(debugHealthComp);
	//scoreComp->AddObserver(debugScoreComp);





	// =========== How To Play? ========
	dae::GameObject* howToPlay = new dae::GameObject();
	howToPlay->SetParent(pRootDemo);
	renderComp = howToPlay->AddComponent<dae::RenderComponent>();
	auto tutorialComp = howToPlay->AddComponent<dae::HowToPlayComponent>();
	renderComp->AddToDisplayGui(tutorialComp);


	// =========== Skip/GoBack Level Buttons ========
	auto skipLevelCommand{ std::make_unique<dae::SkipLevelCommand>() };
	dae::InputManager::GetInstance().BindCommand({SDLK_F4}, dae::InputManager::InputType::OnButtonDown, std::move(skipLevelCommand));

	auto prevLevelCommand{ std::make_unique<dae::GoBackLevelCommand>() };
	dae::InputManager::GetInstance().BindCommand({SDLK_F3}, dae::InputManager::InputType::OnButtonDown, std::move(prevLevelCommand));


}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}