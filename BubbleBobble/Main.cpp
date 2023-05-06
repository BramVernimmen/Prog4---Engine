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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	dae::GameObject* pRootDemo = scene.GetRoot();

	// background
	dae::GameObject* bg = new dae::GameObject();
	auto renderComp = bg->AddComponent<dae::RenderComponent>();
	auto textureComp = bg->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("background.tga");
	textureComp->AddToRenderer(renderComp);
	bg->SetParent(pRootDemo);



	//// logo
	//dae::GameObject* lg = new dae::GameObject();
	//lg->SetParent(pRootDemo);
	//renderComp = lg->AddComponent<dae::RenderComponent>();
	//auto transComp = lg->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(216.f, 180.f);
	//textureComp = lg->AddComponent<dae::TextureComponent>();
	//textureComp->SetTexture("logo.tga");
	//textureComp->AddToRenderer(renderComp);

	//renderComp->AddToDisplayGui(textureComp);
	//renderComp->AddToDisplayGui(transComp);




	//// prog4 text
	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//dae::GameObject* txt = new dae::GameObject();
	//txt->SetParent(pRootDemo);
	//renderComp = txt->AddComponent<dae::RenderComponent>();
	//transComp = txt->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(80, 20);
	//auto textComponent = txt->AddComponent<dae::TextComponent>();
	//textComponent->SetFont(font);
	//textComponent->SetText("Programming 4 Assignment");
	//textComponent->AddToRenderer(renderComp);



	// grid 
	dae::GameObject* grid = new dae::GameObject();
	grid->SetParent(pRootDemo);
	renderComp = grid->AddComponent<dae::RenderComponent>();
	auto gridComp = grid->AddComponent<dae::GridComponent>();
	renderComp->AddToDebug(gridComp);
	auto transComp = grid->GetComponent<dae::TransformComponent>();
	textureComp = grid->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("001_Tile.png");
	transComp->SetLocalPosition(50, 50);
	gridComp->Resize(32, 25);

	// fps
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	dae::GameObject* fps = new dae::GameObject();
	fps->SetParent(pRootDemo);
	renderComp = fps->AddComponent<dae::RenderComponent>();
	 transComp = fps->GetComponent<dae::TransformComponent>();
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
	textureComp = bubby->AddComponent<dae::TextureComponent>();
	textureComp->SetTexture("Bubby.png");
	textureComp->AddToRenderer(renderComp);
	auto healthComp = bubby->AddComponent<dae::HealthComponent>();
	auto scoreComp = bubby->AddComponent<dae::ScoreComponent>();
	healthComp->AddObserver(scoreComp); // our score needs to listen to our own health (for this test)
	auto collision = bubby->AddComponent<dae::BoxCollision>();
	collision->SetSize(48, 48);
	renderComp->AddToDebug(collision);
	auto rigid = bubby->AddComponent<dae::RigidBody>();
	renderComp->AddToDisplayGui(rigid);





	// P1 health debug
	dae::GameObject* debugHealthP1 = new dae::GameObject();
	debugHealthP1->SetParent(pRootDemo);
	renderComp = debugHealthP1->AddComponent<dae::RenderComponent>();
	transComp = debugHealthP1->GetComponent<dae::TransformComponent>();
	transComp->SetLocalPosition(0.0f, 150.0f);
	textComponent = debugHealthP1->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	textComponent->SetFont(font);
	textComponent->SetText("Lives: ");
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
	textComponent->SetText("Score: ");
	textComponent->SetColor({ 0, 255, 0 });
	textComponent->AddToRenderer(renderComp);
	auto debugScoreComp = debugScoreP1->AddComponent<dae::DebugScoreComponent>();

	// add	debug observer to bubby
	healthComp->AddObserver(debugHealthComp);
	scoreComp->AddObserver(debugScoreComp);


	//// bobby - has lives + score
	//dae::GameObject* bobby = new dae::GameObject();
	//bobby->SetParent(pRootDemo);
	//renderComp = bobby->AddComponent<dae::RenderComponent>();
	//auto newTransComp = bobby->GetComponent<dae::TransformComponent>();
	//newTransComp->SetLocalPosition(320.0f, 240.0f);
	//textureComp = bobby->AddComponent<dae::TextureComponent>();
	//textureComp->SetTexture("Bobby.png");
	//textureComp->AddToRenderer(renderComp);
	//healthComp = bobby->AddComponent<dae::HealthComponent>();
	//scoreComp = bobby->AddComponent<dae::ScoreComponent>();
	//healthComp->AddObserver(scoreComp); // our score needs to listen to our own health (for this test)


	// P2 health debug
	//dae::GameObject* debugHealthP2 = new dae::GameObject();
	//debugHealthP2->SetParent(pRootDemo);
	//renderComp = debugHealthP2->AddComponent<dae::RenderComponent>();
	//transComp = debugHealthP2->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(0.0f, 250.0f);
	//textComponent = debugHealthP2->AddComponent<dae::TextComponent>();
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	//textComponent->SetFont(font);
	//textComponent->SetText("Lives: ");
	//textComponent->SetColor({ 130, 210, 255 });
	//textComponent->AddToRenderer(renderComp);
	//debugHealthComp = debugHealthP2->AddComponent<dae::DebugHealthComponent>();
	//debugHealthComp->SetLastHealth(healthComp->GetCurrentHealth());

	// P2 score debug
	//dae::GameObject* debugScoreP2 = new dae::GameObject();
	//debugScoreP2->SetParent(pRootDemo);
	//renderComp = debugScoreP2->AddComponent<dae::RenderComponent>();
	//transComp = debugScoreP2->GetComponent<dae::TransformComponent>();
	//transComp->SetLocalPosition(0.0f, 270.f);
	//textComponent = debugScoreP2->AddComponent<dae::TextComponent>();
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	//textComponent->SetFont(font);
	//textComponent->SetText("Score: ");
	//textComponent->SetColor({ 130, 210, 255 });
	//textComponent->AddToRenderer(renderComp);
	//debugScoreComp = debugScoreP2->AddComponent<dae::DebugScoreComponent>();

	// add	debug observer to bobby
	//healthComp->AddObserver(debugHealthComp);
	//scoreComp->AddObserver(debugScoreComp);



	// =========== How To Play? ========
	dae::GameObject* howToPlay = new dae::GameObject();
	howToPlay->SetParent(pRootDemo);
	renderComp = howToPlay->AddComponent<dae::RenderComponent>();
	auto tutorialComp = howToPlay->AddComponent<dae::HowToPlayComponent>();
	renderComp->AddToDisplayGui(tutorialComp);



	//// bibby
	//dae::GameObject* bibby = new dae::GameObject();
	//bibby->SetParent(pRootDemo);
	//renderComp = bibby->AddComponent<dae::RenderComponent>();
	//newTransComp = bibby->GetComponent<dae::TransformComponent>();
	//newTransComp->SetLocalPosition(260.0f, 310.0f);
	//textureComp = bibby->AddComponent<dae::TextureComponent>();
	//textureComp->SetTexture("Bibby.png");
	//textureComp->AddToRenderer(renderComp);


	// ======== damage/point commands ============

	// P1
	std::vector<unsigned int> p1DamageButtonsInput{
		SDLK_j
	};
	auto p1DamageCommand{ std::make_unique<dae::DamageCommand>(bubby, 1) };
	dae::InputManager::GetInstance().BindCommand(p1DamageButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p1DamageCommand));

	std::vector<unsigned int> p1GiveScoreButtonsInput{
		SDLK_u
	};
	auto p1ScoreCommand{ std::make_unique<dae::GiveScoreCommand>(bubby, 100) };
	dae::InputManager::GetInstance().BindCommand(p1GiveScoreButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p1ScoreCommand));


	// P2
	//std::vector<unsigned int> p2DamageButtonsInput{
	//	SDLK_k
	//};
	//auto p2DamageCommand{ std::make_unique<dae::DamageCommand>(bobby, 1) };
	//dae::InputManager::GetInstance().BindCommand(p2DamageButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p2DamageCommand));

	//std::vector<unsigned int> p2GiveScoreButtonsInput{
	//	SDLK_i
	//};
	//auto p2ScoreCommand{ std::make_unique<dae::GiveScoreCommand>(bobby, 100) };
	//dae::InputManager::GetInstance().BindCommand(p2GiveScoreButtonsInput, dae::InputManager::InputType::OnButtonDown, std::move(p2ScoreCommand));



	// ========= Move Commands ===============

	const float baseSpeed{ 100.0f };
	const float baseJumpStrength{ 250.0f };
	std::vector<unsigned int> character1Input{
		SDLK_a,
		SDLK_d,
		SDLK_w,
		SDLK_s,
	};
	auto character1MoveCommand{ std::make_unique<dae::MoveCommand>(bubby, baseSpeed, baseJumpStrength) };
	dae::InputManager::GetInstance().BindCommand(character1Input, dae::InputManager::InputType::Digital2DAxis, std::move(character1MoveCommand));

	//std::vector<unsigned int> character2Input{
	//	dae::Controller::ControllerButton::DPadLeft,
	//	dae::Controller::ControllerButton::DPadRight,
	//	dae::Controller::ControllerButton::DPadUp,
	//	dae::Controller::ControllerButton::DPadDown
	//};
	//
	//auto character2MoveCommand{ std::make_unique<dae::MoveCommand>(bobby, baseSpeed * 2.0f) };
	//dae::InputManager::GetInstance().BindCommand(character2Input, dae::InputManager::InputType::Digital2DAxis, std::move(character2MoveCommand), 0);




	// EXTRA: 3rd character with left joystick input
	//std::vector<unsigned int> character3Input{
	//	dae::Controller::ControllerButton::LeftThumb
	//};
	//
	//auto character3MoveCommand{ std::make_unique<dae::MoveCommand>(bibby, baseSpeed * 2.0f) };
	//dae::InputManager::GetInstance().BindCommand(character3Input, dae::InputManager::InputType::Analog2DAxis, std::move(character3MoveCommand), 1);












	// =========================== UNUSED PARENTING - STILL NEEDING FIX ===========================

	//fps->SetParent(bubby);
	//fps->SetParent(bobby, true);
	//bobby->SetParent(bubby, true);

	//bubby->SetParent(bobby);
	//bobby->SetParent(bubby);




}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}