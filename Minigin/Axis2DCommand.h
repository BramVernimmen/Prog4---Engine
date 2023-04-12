#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{

	class Axis2DCommand : public Command
	{
	public:
		virtual ~Axis2DCommand() = default;
		virtual void Execute() override = 0;

		void SetInput(const glm::vec2& newInput) { m_InputValue = newInput; }

	protected:
		glm::vec2 m_InputValue{};
	};

}
