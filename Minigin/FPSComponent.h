#pragma once
#include "UpdateComponent.h"
namespace dae
{
	class TextComponent;
	class FPSComponent : public UpdateComponent
	{
	public:
		FPSComponent(std::shared_ptr<GameObject>& pParent);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		virtual void Update() override;

		std::shared_ptr<TextComponent> GetTextComponent() const { return m_pPersonalTextComponent; }


	private:
		std::shared_ptr<TextComponent> m_pPersonalTextComponent{};
		float m_TimeRunning{ 0.99f };
	};

}

