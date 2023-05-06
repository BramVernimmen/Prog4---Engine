#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class RigidBody;
	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		void AddRigidBody(dae::RigidBody* rigidbodyToAdd);
		void RemoveRigidBody(dae::RigidBody* rigidBodyToRemove);

		void Update();

		void SetGravity(float newGravity) { m_Gravity = newGravity; }
	protected:

	private:
		std::vector<dae::RigidBody*> m_pRigidBodies{};
		//float m_Gravity{ -9.81f }; // way too slow
		float m_Gravity{ -200.0f };

	};

}
