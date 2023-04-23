#include "FPSComponent.h"
#include "TextComponent.h"
#include "Time.h"
#include "GameObject.h"
#include <algorithm>
#include <numeric>

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pPersonalTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void dae::FPSComponent::Update()
{
	const float dt{ Time::GetInstance().GetDeltaTime() };
	m_TimeRunning += dt;

	if (m_TimeRunning < m_TimeLimit) // branch prediction: more likely to land here
	{
		m_PastDeltatimes.push_back(dt);
	}
	else
	{
		// 1 / deltatime will give the correct fps :)
		// first calculate average deltaTime
		const float avgDT{ std::accumulate(m_PastDeltatimes.begin(), m_PastDeltatimes.end(), 0.0f) / m_PastDeltatimes.size() };
		m_PastDeltatimes.clear();
		m_pPersonalTextComponent->SetText(std::to_string(static_cast<int>(1.f / avgDT)) + " FPS");

		// the TextComponent is not a direct child of the GameObject, so it will not update automatically
		m_TimeRunning -= m_TimeLimit;
	}
	
}
