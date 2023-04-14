#include "Subject.h"
#include "Observer.h"
#include "Event.h"
#include <iostream>


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

void dae::Subject::NotifyObservers(Event&& currEvent, std::any payload)
{
	for (auto currObserver : m_pObservers)
	{
		if (currObserver) // safety check
		{
			// we cannot use std::move(currEvent), this will move the currEvent, creating perhaps problems for the next iteration
			// C26800; use of a moved from object lifetime 1 c++
			// this will only appear if our destination is an Event&& but won't give this warning when we use const Event& 
			currObserver->Notify(currEvent, payload);
		}
	}
}
