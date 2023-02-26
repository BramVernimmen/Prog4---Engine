#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{	
	class Time : public Singleton<Time>
	{
	public:
		float GetDeltaTime() const { return m_DeltaTime; }
		float GetTotalTime() const { return m_TotalTime; }
		void Update();
	protected:

	private:
		std::chrono::steady_clock::time_point m_LastTime{std::chrono::high_resolution_clock::now()};
		float m_DeltaTime{0.0f};
		float m_TotalTime{0.0f};
	};
}


