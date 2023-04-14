#pragma once
#include "Singleton.h"
#include "Observer.h"


namespace dae
{
	class Event;
	class AchievementObserver final : public Singleton<AchievementObserver>, public Observer
	{
	public:
		virtual void Notify(const Event& currEvent, std::any payload = nullptr) override;
		void ClearAchievements();

	private:
		void UnlockAchievement(const char* ID);
	};

}
