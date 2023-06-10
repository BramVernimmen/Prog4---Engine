#pragma once
#include "Singleton.h"
#include "Observer.h"
#include "GameObject.h"
#include "SDL_keycode.h"
#include "Controller.h"
#include "InputManager.h"

namespace dae
{
	struct PlayerInfo
	{
		std::string m_TexturePath{"Bibby.png" };
		int m_CollisionSizeX{48};
		int m_CollisionSizeY{48};
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

		unsigned int m_PlayerCount{ 2 };
	};
}
