#include "RigidBody.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TransformComponent.h"
#include "PhysicsManager.h"
#include "imgui.h"

dae::RigidBody::RigidBody(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pTransform = GetOwner()->GetComponent<dae::TransformComponent>();
	dae::PhysicsManager::GetInstance().AddRigidBody(this);
}

dae::RigidBody::~RigidBody()
{
	dae::PhysicsManager::GetInstance().RemoveRigidBody(this);
}

void dae::RigidBody::Update()
{
	if (m_IsKinematic)
		return;

	glm::vec2 offset = m_Velocity;
	offset *= dae::GameTime::GetInstance().GetDeltaTime();
	const auto& localPos{ m_pTransform->GetLocalPosition() };
	// update the position
	m_pTransform->SetLocalPosition(offset.x + localPos.x, localPos.y - offset.y);

	m_DisplayVelocity = m_Velocity;

}

void dae::RigidBody::DisplayGui()
{
	ImGui::Begin("RigidBody Debug");

	ImGui::Text("Current Velocity.x = %f", m_DisplayVelocity.x);
	ImGui::Text("Current Velocity.y = %f", m_DisplayVelocity.y);
	
	ImGui::Text("Is Grounded = %s", m_IsGrounded ? "true" : "false");

	ImGui::End();

}
