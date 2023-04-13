#pragma once
#include <any>

namespace dae
{
	class Event;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(Event event, std::any source = nullptr) = 0;
	};
}

