#pragma once
#include "UpdateComponent.h"

namespace dae
{

	class MainMenuComponent final : public UpdateComponent
	{
	public:
		MainMenuComponent(GameObject* pOwner);
		~MainMenuComponent() = default;
		MainMenuComponent(const MainMenuComponent& other) = delete;
		MainMenuComponent(MainMenuComponent&& other) = delete;
		MainMenuComponent& operator=(const MainMenuComponent& other) = delete;
		MainMenuComponent& operator=(MainMenuComponent&& other) = delete;

		virtual void Update() override {};
		virtual void DisplayGui() override;

	private:
	};

}

