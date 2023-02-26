#include "Time.h"

void dae::Time::Update()
{
	const auto currentTime{ std::chrono::high_resolution_clock::now() };
	m_TotalTime += m_DeltaTime;
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();

	m_LastTime = currentTime;
}
