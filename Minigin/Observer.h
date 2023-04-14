#pragma once
#include <any>

namespace dae
{
	class Event;
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& currEvent, std::any payload = nullptr) = 0;
	};
}

