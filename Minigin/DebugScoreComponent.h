#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "EngineEvents.h"

namespace dae
{
	class TextComponent;
	class DebugScoreComponent final : public UpdateComponent, public Observer
	{
	public:
		DebugScoreComponent(GameObject* pOwner);
		~DebugScoreComponent() = default;
		DebugScoreComponent(const DebugScoreComponent& other) = delete;
		DebugScoreComponent(DebugScoreComponent&& other) = delete;
		DebugScoreComponent& operator=(const DebugScoreComponent& other) = delete;
		DebugScoreComponent& operator=(DebugScoreComponent&& other) = delete;


		virtual void Update() override;

		virtual void Notify(const Event& currEvent, std::any payload) override;


	private:
		TextComponent* m_pPersonalTextComponent{};
		int m_CurrentScoreToPrint{ 0 };
		bool m_ShouldUpdateText{ true };

	};

}
