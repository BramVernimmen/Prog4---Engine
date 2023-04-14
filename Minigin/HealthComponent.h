#pragma once
#include "UpdateComponent.h"
#include "Subject.h"

namespace dae
{

	class HealthComponent: public UpdateComponent, public Subject
	{
	public:
		HealthComponent(std::weak_ptr<GameObject> pOwner);
		~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;


		virtual void Update() override {};

		void SetMaxHealth(int newMax) { m_MaxHealth = newMax; }
		void ResetHealth();
		int GetCurrentHealth() { return m_CurrentHealth; }
		void DoDamage(int damage);

	private:
		int m_CurrentHealth{};
		int m_MaxHealth{5};


	};

}
