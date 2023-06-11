#include "PhysicsManager.h"
#include "RigidBody.h"
#include "GameTime.h"

void dae::PhysicsManager::AddRigidBody(dae::RigidBody* rigidbodyToAdd)
{
	auto foundIt = std::find_if(m_pRigidBodies.begin(), m_pRigidBodies.end(), [rigidbodyToAdd](UpdateComponent* currElement)
		{ return currElement == rigidbodyToAdd; });

	if (foundIt == m_pRigidBodies.end()) // if we reach the end, add it
		m_pRigidBodies.emplace_back(rigidbodyToAdd);
}

void dae::PhysicsManager::RemoveRigidBody(dae::RigidBody* rigidBodyToRemove)
{
	auto foundIt = std::find_if(m_pRigidBodies.begin(), m_pRigidBodies.end(), [rigidBodyToRemove](UpdateComponent* currElement)
		{ return currElement == rigidBodyToRemove; });

	if (foundIt != m_pRigidBodies.end()) // if we don't reach the end, remove it
		m_pRigidBodies.erase(foundIt);
}

void dae::PhysicsManager::Update()
{
	const float dt{ dae::GameTime::GetInstance().GetDeltaTime() };

	for (const auto& currRigidBody : m_pRigidBodies)
	{
		if (currRigidBody->IsKinematic() || currRigidBody->IsGrounded() || currRigidBody->IgnoresGravity())
			continue;

		auto currVelocity = currRigidBody->GetVelocity();

		currVelocity.y += m_Gravity * dt;

		currRigidBody->SetVelocity(currVelocity);
	}
}
