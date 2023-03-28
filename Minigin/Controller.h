#pragma once
#include "glm/glm.hpp"
#include <memory>

namespace dae 
{
	class Controller final
	{
		class ControllerImpl;
		//ControllerImpl* pImpl;
		std::unique_ptr<ControllerImpl> pImpl;
	public :
		// using enum instead of enum class makes us capable of initializing them with unsigned int and no need for a cast
		enum ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			LeftTrigger = 0x0400,	// WILL NOT WORK AS WBUTTON
			RightTrigger = 0x0800,	// WILL NOT WORK AS WBUTTON
			ButtonA = 0x1000, 
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};


		explicit Controller(int controllerIndex);
		~Controller();

		void Update();

		bool IsDown(unsigned int button) const;
		bool IsUp(unsigned int button) const;
		bool IsPressed(unsigned int button) const;
		float GetAxis(unsigned int button) const;
		glm::vec2 Get2DAxis(unsigned int button) const;

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
	};
}

