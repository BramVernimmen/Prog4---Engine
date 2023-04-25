#include "GameTime.h"

void dae::GameTime::Update()
{
	//const auto currentTime{ std::chrono::high_resolution_clock::now() };
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_TotalTime += m_DeltaTime;
	m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();

	m_LastTime = m_CurrentTime;

}
