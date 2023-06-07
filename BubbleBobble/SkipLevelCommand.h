#pragma once
#include "Command.h"
namespace dae
{

	class SkipLevelCommand : public Command
	{
	public:
		SkipLevelCommand() = default;
		~SkipLevelCommand() = default;

		SkipLevelCommand(const SkipLevelCommand& other) = delete;
		SkipLevelCommand(SkipLevelCommand&& other) = delete;
		SkipLevelCommand& operator=(const SkipLevelCommand& other) = delete;
		SkipLevelCommand& operator=(SkipLevelCommand&& other) = delete;


		virtual void Execute() override;
	};

}