#pragma once
#include "UpdateComponent.h"
#include <vector>

namespace dae
{
	class TextComponent;
	class FPSComponent final : public UpdateComponent
	{
	public:
		FPSComponent(GameObject* pOwner);
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		virtual void Update() override;

		//std::shared_ptr<TextComponent> GetTextComponent() const { return m_pPersonalTextComponent; }


	private:
		TextComponent* m_pPersonalTextComponent{};
		float m_TimeRunning{ 0.99f };
		const float m_TimeLimit{ 1.0f };
		std::vector<float> m_PastDeltatimes{};
	};

}

