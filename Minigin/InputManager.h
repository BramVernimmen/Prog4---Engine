#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Controller.h"
#include "Command.h"
#include <map>
#include <unordered_set>
#include <glm/glm.hpp>

// difference between analog and digital:
// analog will give a range of values, mostly used in joysticks and triggers
// digital will give a bool, value of 0 or 1

// so we need to keep these in mind

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputType
		{
			OnButtonDown,
			OnButtonUp,
			OnButton,
			AnalogAxis, // will use 1 button -> will return a float from -1 to 1
			Analog2DAxis, // will use 1 button -> will return a vec2
			Digital2DAxis // will use 4 buttons -> will return a vec2; order of buttons: LEFT, RIGHT, UP, DOWN
		};

		struct InputInfo
		{
			int id{};
			std::vector<unsigned int> buttons{};
			InputType inputType{};
		public:
			// we need this for when we emplace something in a map
			bool operator<(const InputInfo& other) const { return other.id < id; }
		};

		bool ProcessInput();

		void BindCommand(const std::vector<unsigned int>& buttons, InputType inputType, std::unique_ptr<Command> pCommand, int id = -1); // default to keyboard

		const glm::vec2& Get2DAxisValue() const { return m_2DAxisValue; }
		float GetAnalogAxisValue() const { return m_AnalogAxisValue; }

	private:
		std::vector<std::unique_ptr<dae::Controller>> m_pControllers{};

		std::multimap<InputInfo, std::unique_ptr<Command>> m_Commands{};


		glm::vec2 m_2DAxisValue{};
		float m_AnalogAxisValue{};


		std::unordered_set<unsigned int> m_KeysDown{};
		std::unordered_set<unsigned int> m_KeysPressed{};
		std::unordered_set<unsigned int> m_KeysUp{};

		bool ReadSDL_Events();
		void ControllerIndexCheck(int id);
		void ResetValues();
	};

}
