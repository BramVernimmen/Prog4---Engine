#include "FPSComponent.h"
#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject>& pParent)
	: UpdateComponent(pParent)
{
	m_pPersonalTextComponent = std::make_shared<TextComponent>(pParent);
}

void dae::FPSComponent::Update()
{
	m_TimeRunning += Time::GetInstance().GetDeltaTime();
	const float timeLimit{ 1.0f };

	if (m_TimeRunning >= timeLimit)
	{
		// 1 / deltatime will give the correct fps :)
		m_pPersonalTextComponent->SetText(std::to_string(static_cast<int>(1.f / Time::GetInstance().GetDeltaTime())) + " FPS");
		m_pPersonalTextComponent->Update(); // don't forget to update the TextComponent
		// the TextComponent is not a direct child of the GameObject, so it will not update automatically
		m_TimeRunning -= timeLimit;
	}
	
}
