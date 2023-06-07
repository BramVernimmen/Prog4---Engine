#pragma once
#include "Command.h"
namespace dae
{

	class GoBackLevelCommand : public Command
	{
	public:
		GoBackLevelCommand() = default;
		~GoBackLevelCommand() = default;

		GoBackLevelCommand(const GoBackLevelCommand& other) = delete;
		GoBackLevelCommand(GoBackLevelCommand&& other) = delete;
		GoBackLevelCommand& operator=(const GoBackLevelCommand& other) = delete;
		GoBackLevelCommand& operator=(GoBackLevelCommand&& other) = delete;


		virtual void Execute() override;
	};

}