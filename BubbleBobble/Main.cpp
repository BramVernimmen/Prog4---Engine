#include <SDL.h>

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
#include "HealthComponent.h"
#include "DebugHealthComponent.h"
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

void load()
{

	auto scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto testScene = dae::SceneManager::GetInstance().CreateScene("TEST");
	dae::GameObject* pRootDemo = scene->GetRoot();

	dae::SceneManager::GetInstance().RemoveScene(testScene);
	dae::SceneManager::GetInstance().AddScene(testScene);


	dae::ServiceLocator::SetSoundSystem(new dae::SdlSoundSystem());
	//dae::ServiceLocator::SetSoundSystem(new dae::LoggingSoundSystem(new dae::SdlSoundSystem));
	//auto& ss = dae::ServiceLocator::GetSoundSystem();

	//ss.Load(0, "Sounds/Pickup.wav");
	//ss.Play(0);



	// grid 
	//dae::GameObject* grid = new dae::GameObject();
	//grid->SetParent(pRootDemo);
	//auto renderGridComp = grid->AddComponent<dae::RenderComponent>();
	//auto gridComp = grid->AddComponent<dae::GridComponent>();
	//renderGridComp->AddToDebug(gridComp);
	//auto transGridComp = grid->GetComponent<dae::TransformComponent>();
	//auto textureGridComp = grid->AddComponent<dae::TextureComponent>();
	//textureGridComp->SetTexture("Tiles/001_Tile.png");
	//gridComp->SetTileLayout("XXXXXXXXXXXXXXX--XXXXXXXXXXXXXXXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX||---||||||||||||||||||---||XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX||---||||||||||||||||||---||XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX||---||||||||||||||||||---||XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXX----------------------------XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	//transGridComp->SetLocalPosition(50, 50);
	//gridComp->Resize(32, 25);


	// level loader
	dae::GameObject* levelLoader = new dae::GameObject();
	levelLoader->SetParent(pRootDemo);
	auto levelLoaderComp = levelLoader->AddComponent<dae::LevelLoaderComponent>();
	levelLoaderComp->AddLevelFile("Levels/001.txt");
	levelLoaderComp->SetTileTextureLocation("Tiles/");
	levelLoaderComp->SetTileTextureExtension("_Tile.png");
	levelLoaderComp->SetGridOffset(50, 50);
	levelLoaderComp->SetGridSize(32, 25);
	levelLoaderComp->CreateLevels();

	// fps
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
	//auto test = fps->GetComponent<dae::RenderComponent>(); test;
	fps->AddComponent<dae::FPSComponent>(); //auto FPSComponent =  // just write this down, otherwise warning as unused


	// bubby - has lives + score (P1)
	dae::GameObject* bubby = new dae::GameObject();
	bubby->SetParent(pRootDemo);
	renderComp = bubby->AddComponent<dae::RenderComponent>();
	transComp = bubby->GetComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(220.0f, 210.0f);
	auto textureComp = bubby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bubby.png");
	textureComp->AddToRenderer(renderComp);
	auto healthComp = bubby->AddComponent<dae::HealthComponent>();
	auto scoreComp = bubby->AddComponent<dae::ScoreComponent>();
	healthComp->AddObserver(scoreComp); // our score needs to listen to our own health (for this test)
	auto collision = bubby->AddComponent<dae::BoxCollision>();
	collision->SetSize(48, 48);
	renderComp->AddToDebug(collision);

	bubby->AddComponent<dae::RigidBody>();




	// P1 health debug
	dae::GameObject* debugHealthP1 = new dae::GameObject();
	debugHealthP1->SetParent(pRootDemo);
	renderComp = debugHealthP1->AddComponent<dae::RenderComponent>();
	transComp = debugHealthP1->GetComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 150.0f);
	textComponent = debugHealthP1->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetColor({ 0, 255, 0 });
	textComponent->AddToRenderer(renderComp);
	auto debugHealthComp = debugHealthP1->AddComponent<dae::DebugHealthComponent>();
	debugHealthComp->SetLastHealth(healthComp->GetCurrentHealth());

	// P1 score debug
	dae::GameObject* debugScoreP1 = new dae::GameObject();
	debugScoreP1->SetParent(pRootDemo);
	renderComp = debugScoreP1->AddComponent<dae::RenderComponent>();
	transComp = debugScoreP1->GetComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 170.f);
	textComponent = debugScoreP1->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetColor({ 0, 255, 0 });
	textComponent->AddToRenderer(renderComp);
	auto debugScoreComp = debugScoreP1->AddComponent<dae::DebugScoreComponent>();

	// add	debug observer to bubby
	healthComp->AddObserver(debugHealthComp);
	scoreComp->AddObserver(debugScoreComp);





	// =========== How To Play? ========
	dae::GameObject* howToPlay = new dae::GameObject();
	howToPlay->SetParent(pRootDemo);
	renderComp = howToPlay->AddComponent<dae::RenderComponent>();
	auto tutorialComp = howToPlay->AddComponent<dae::HowToPlayComponent>();
	renderComp->AddToDisplayGui(tutorialComp);


	// ========= Move Commands ===============

	const float baseSpeed{ 100.0f };
	const float baseJumpStrength{ 250.0f };
	std::vector<unsigned int> character1Input{
		SDLK_a,
		SDLK_d,
		SDLK_w,
		SDLK_s,
	};
	auto character1MoveCommand{ std::make_unique<dae::MoveCommand>(bubby, baseSpeed, baseJumpStrength, static_cast<unsigned short>(1), "Sounds/Jump.wav") };
	dae::InputManager::GetInstance().BindCommand(character1Input, dae::InputManager::InputType::Digital2DAxis, std::move(character1MoveCommand));




	std::vector<unsigned int> skipSceneInput{
		SDLK_F4
	};

	auto skipLevelCommand{ std::make_unique<dae::SkipLevelCommand>() };
	dae::InputManager::GetInstance().BindCommand(skipSceneInput, dae::InputManager::InputType::OnButtonDown, std::move(skipLevelCommand));


	std::vector<unsigned int> prevSceneInput{
		SDLK_F3
	};
	auto prevLevelCommand{ std::make_unique<dae::GoBackLevelCommand>() };
	dae::InputManager::GetInstance().BindCommand(prevSceneInput, dae::InputManager::InputType::OnButtonDown, std::move(prevLevelCommand));


}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}