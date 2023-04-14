#pragma once
#include "UpdateComponent.h"

namespace dae
{

	class HowToPlayComponent final : public UpdateComponent
	{
	public:
		HowToPlayComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~HowToPlayComponent() = default;
		HowToPlayComponent(const HowToPlayComponent& other) = delete;
		HowToPlayComponent(HowToPlayComponent&& other) = delete;
		HowToPlayComponent& operator=(const HowToPlayComponent& other) = delete;
		HowToPlayComponent& operator=(HowToPlayComponent&& other) = delete;

		virtual void Update() override {};
		virtual void DisplayGui() override;

	protected:

	private:
		bool m_IsOpen{ true };
	};

}
