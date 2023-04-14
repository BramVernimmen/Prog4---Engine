#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;
	class HealthComponent;
	class DamageCommand : public Command
	{
	public:
		DamageCommand(GameObject* pGameObject, int damage);
		~DamageCommand() = default;
	
		DamageCommand(const DamageCommand& other) = delete;
		DamageCommand(DamageCommand&& other) = delete;
		DamageCommand& operator=(const DamageCommand& other) = delete;
		DamageCommand& operator=(DamageCommand&& other) = delete;
	
	
		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		HealthComponent* m_pHealth{};
		int m_Damage{1};
	};
}

