#include "AchievementObserver.h"
#include "EngineEvents.h"
#include "ScoreComponent.h"
#include <isteamuserstats.h>

void dae::AchievementObserver::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(GainedScore)) // handle things here
	{
		if (payload.type() == typeid(ScoreComponent*))
		{
			// handle payload
			int currentScore{ std::any_cast<ScoreComponent*>(payload)->GetCurrentScore() };
			if (currentScore >= 500) // unlock achievement
			{
				UnlockAchievement("ACH_WIN_ONE_GAME");
			}
		}
	}
}

void dae::AchievementObserver::ClearAchievements()
{
	//SteamUserStats()->ClearAchievement("ACH_WIN_ONE_GAME");
	SteamUserStats()->ResetAllStats(true);
}

void dae::AchievementObserver::UnlockAchievement(const char* ID)
{
	bool isAchieved{ false };
	SteamUserStats()->GetAchievement(ID, &isAchieved);

	if (isAchieved)
		return;

	SteamUserStats()->SetAchievement(ID);
	SteamUserStats()->StoreStats();
}
