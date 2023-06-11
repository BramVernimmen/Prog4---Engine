#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "GameObject.h"
#include "SDL_keycode.h"
#include "SDL_pixels.h"
#include "Controller.h"
#include "InputManager.h"

namespace dae
{
	struct PlayerInfo
	{
		// base player info
		std::string m_TexturePath{"Bibby.png" };
		int m_CollisionSizeX{35};
		int m_CollisionSizeY{48};

		// movement info
		bool m_UseKeyboard{ true };
		std::vector<unsigned int> m_KeyBoardInputs{SDLK_a, SDLK_d, SDLK_w, SDLK_s};
		InputManager::InputType m_KeyboardInputType{InputManager::InputType::Digital2DAxis};
		bool m_UseController{ false };
		std::vector<unsigned int> m_ControllerInputs{Controller::ControllerButton::DPadLeft, 
													Controller::ControllerButton::DPadRight, 
													Controller::ControllerButton::DPadUp, 
													Controller::ControllerButton::DPadDown };
		InputManager::InputType m_ControllerInputType{InputManager::InputType::Digital2DAxis};
		float m_BaseSpeed{ 100.0f };
		float m_BaseJumpStrength{ 250.0f };
		unsigned short m_JumpSoundId{ static_cast<unsigned short>(1) };
		std::string m_JumpSoundPath{"Sounds/Jump.wav"};

		// display info
		float m_DisplayTopLeftX{0.0f};
		float m_DisplayTopLeftY{0.0f};
		std::string m_FontPath{"Lingua.otf"};
		int m_FontSize{ 24 };
		Uint8 m_FontColorR{255};
		Uint8 m_FontColorG{255};
		Uint8 m_FontColorB{255};

	};

	class Scene;
	class PlayerManager final : public Singleton<PlayerManager>, public Observer
	{
	public:

		void SetPlayerCount(unsigned int playerCount) { m_PlayerCount = playerCount; }
		void AddPlayerInfo(const PlayerInfo& playerInfo) { m_PlayerInfo.emplace_back(playerInfo); }

		void Notify(const Event& currEvent, std::any payload = nullptr) override;

	private:
		void CreatePlayers(GameObject* pRoot);
		std::vector<GameObject*> m_pPlayers{};
		std::vector<PlayerInfo> m_PlayerInfo{};
		std::vector<std::vector<GameObject*>> m_pPlayerDebugs{}; // each player has multiple debug components, cache them here
		std::vector<std::vector<Command*>> m_pPlayerCommands{}; // this way each player has their own vector of commands

		unsigned int m_PlayerCount{ 0 };
	};
}
