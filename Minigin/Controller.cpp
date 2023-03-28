#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
//#pragma comment(lib, "xinput.lib")

#include "Controller.h"
#include <algorithm>

using namespace dae;

class Controller::ControllerImpl
{
public:
	ControllerImpl(int controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		m_ControllerIndex = static_cast<unsigned int>(controllerIndex);
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

	float GetAxis(unsigned int button) const
	{
		float returnValue{0.0f};
		if (button & ControllerButton::LeftTrigger)
		{
			returnValue = m_CurrentState.Gamepad.bLeftTrigger / m_MaxTriggerAxisValue;
		}
		else // it's the right trigger, there is no other way
		{
			returnValue =m_CurrentState.Gamepad.bRightTrigger / m_MaxTriggerAxisValue;
		}
		return returnValue;
	}
	glm::vec2 Get2DAxis(unsigned int button) const
	{
		glm::vec2 returnVector{};
		// first check which stick we need
		//const bool leftStick{ button & ControllerButton::LeftThumb };
		if (button & ControllerButton::LeftThumb) // read left stick values
		{
			returnVector.x = HandleAxisDeadZoneAndClamp(m_CurrentState.Gamepad.sThumbLX);
			returnVector.y = HandleAxisDeadZoneAndClamp(m_CurrentState.Gamepad.sThumbLY);
		}
		else // read right stick values
		{
			returnVector.x = HandleAxisDeadZoneAndClamp(m_CurrentState.Gamepad.sThumbRX);
			returnVector.y = HandleAxisDeadZoneAndClamp(m_CurrentState.Gamepad.sThumbRY);
		}
		return returnVector;
	}

private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame;
	WORD m_ButtonsReleasedThisFrame;

	unsigned int m_ControllerIndex;

	const float m_MaxAxisValueSticks{ 32767.0f };
	const float m_MaxTriggerAxisValue{ 255.0f };
	// take the default windows deadzone value, use the right stick as this value will be bigger
	const int m_DeadZoneValue{ static_cast<int>(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) };

	float HandleAxisDeadZoneAndClamp(float readValue) const
	{
		if (std::abs(readValue) < m_DeadZoneValue) // we are in the deadzone, set to 0
		{
			readValue = 0.0f;
		}
		else
		{
			readValue /= m_MaxAxisValueSticks; // if value is negative we will get a very small float precision error, clamp it away
			readValue = std::clamp(readValue, -1.0f, 1.0f);
		}
		return readValue;
	}
};



Controller::Controller(int controllerIndex)
	: pImpl{ std::make_unique<ControllerImpl>(controllerIndex) }
{}

dae::Controller::~Controller() = default;



void Controller::Update()
{
	pImpl->Update();
}

bool Controller::IsDown(unsigned int button) const
{
	return pImpl->IsDownThisFrame(button);
}

bool Controller::IsUp(unsigned int button) const
{
	return pImpl->IsUpThisFrame(button);
}

bool Controller::IsPressed(unsigned int button) const
{
	return pImpl->IsPressed(button);
}

float dae::Controller::GetAxis(unsigned int button) const
{
	return pImpl->GetAxis(button);
}

glm::vec2 dae::Controller::Get2DAxis(unsigned int button) const
{
	return pImpl->Get2DAxis(button);
}

