#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;
	class LivesComponent;
	class DamageCommand : public Command
	{
	public:
		DamageCommand(GameObject* pGameObject);
		~DamageCommand() = default;
	
		DamageCommand(const DamageCommand& other) = delete;
		DamageCommand(DamageCommand&& other) = delete;
		DamageCommand& operator=(const DamageCommand& other) = delete;
		DamageCommand& operator=(DamageCommand&& other) = delete;
	
	
		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		LivesComponent* m_pLives{};
	};
}

