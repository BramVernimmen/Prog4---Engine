#include "Subject.h"
#include "Observer.h"
#include "Event.h"

void dae::Subject::AddObserver(Observer* observerToAdd)
{
	m_pObservers.push_back(observerToAdd);
}

void dae::Subject::RemoveObserver(Observer* observerToRemove)
{
	for (auto it{ m_pObservers.begin()}; it != m_pObservers.end(); ++it)
	{
		if (*it == observerToRemove)
		{
			m_pObservers.erase(it);
			return;
		}
	}
}

void dae::Subject::NotifyObservers(Event event, std::any source)
{
	for (auto currObserver : m_pObservers)
	{
		if (currObserver) // safety check
		{
			currObserver->Notify(event, source);
		}
	}
}
