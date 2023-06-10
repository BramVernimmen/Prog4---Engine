#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "GameEvents.h"

namespace dae
{
	class TextComponent;
	class DebugLivesComponent final : public UpdateComponent, public Observer
	{
	public:
		DebugLivesComponent(GameObject* pOwner);
		~DebugLivesComponent() = default;
		DebugLivesComponent(const DebugLivesComponent& other) = delete;
		DebugLivesComponent(DebugLivesComponent&& other) = delete;
		DebugLivesComponent& operator=(const DebugLivesComponent& other) = delete;
		DebugLivesComponent& operator=(DebugLivesComponent&& other) = delete;
	
	
		virtual void Update() override;
	
		virtual void Notify(const Event& currEvent, std::any payload) override;

		void SetLastLives(int lastLives);

	private:
		TextComponent* m_pPersonalTextComponent{};

		int m_LastLives{};
		bool m_ShouldUpdateText{ false };


	};
}

