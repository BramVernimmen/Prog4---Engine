#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;
	class ScoreComponent;
	class GiveScoreCommand : public Command
	{
	public:
		GiveScoreCommand(GameObject* pGameObject, int damage);
		~GiveScoreCommand() = default;

		GiveScoreCommand(const GiveScoreCommand& other) = delete;
		GiveScoreCommand(GiveScoreCommand&& other) = delete;
		GiveScoreCommand& operator=(const GiveScoreCommand& other) = delete;
		GiveScoreCommand& operator=(GiveScoreCommand&& other) = delete;


		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		ScoreComponent* m_pScore{};
		int m_ScoreValue{ 100 };
	};
}
