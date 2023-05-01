#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "EngineEvents.h"

namespace dae
{
	class TextComponent;
	class DebugHealthComponent final : public UpdateComponent, public Observer
	{
	public:
		DebugHealthComponent(GameObject* pOwner);
		~DebugHealthComponent() = default;
		DebugHealthComponent(const DebugHealthComponent& other) = delete;
		DebugHealthComponent(DebugHealthComponent&& other) = delete;
		DebugHealthComponent& operator=(const DebugHealthComponent& other) = delete;
		DebugHealthComponent& operator=(DebugHealthComponent&& other) = delete;
	
	
		virtual void Update() override;
	
		virtual void Notify(const Event& currEvent, std::any payload) override;

		void SetLastHealth(int lastHealth);

	private:
		TextComponent* m_pPersonalTextComponent{};

		int m_LastHealth{};
		bool m_ShouldUpdateText{ false };


	};
}

