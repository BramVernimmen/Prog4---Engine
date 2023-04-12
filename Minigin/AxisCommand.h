#pragma once
#include "Command.h"
namespace dae
{

	class AxisCommand : public Command
	{
	public:
		virtual ~AxisCommand() = default;
		virtual void Execute() override = 0;

		void SetInput(float newInput) { m_InputValue = newInput; }

	protected:
		float m_InputValue{};
	};

}
