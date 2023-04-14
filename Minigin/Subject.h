#pragma once

#include <vector>
#include <any>

namespace dae
{
	class Observer;
	class Event;
	class Subject 
	{
	public:
		virtual ~Subject() = default;
		void AddObserver(Observer* observerToAdd);
		void RemoveObserver(Observer* observerToRemove);

	protected:
		void NotifyObservers(Event&& currEvent, std::any payload = nullptr);

	private:
		std::vector<Observer*> m_pObservers{};
	};

}
