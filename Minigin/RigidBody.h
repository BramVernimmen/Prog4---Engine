#pragma once
#include "UpdateComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class RigidBody final : public UpdateComponent
	{
	public:
		RigidBody(GameObject* pOwner);
		~RigidBody();
		RigidBody(const RigidBody& other) = delete;
		RigidBody(RigidBody&& other) = delete;
		RigidBody& operator=(const RigidBody& other) = delete;
		RigidBody& operator=(RigidBody&& other) = delete;


		virtual void Update() override;
		virtual void DisplayGui() override;

		void SetKinematic(bool newState) { m_IsKinematic = newState; }
		void SetVelocity(glm::vec2 newVelocity) { m_Velocity = newVelocity; }
		void SetGrounded(bool isGrounded = true) { m_IsGrounded = isGrounded; }

		glm::vec2 GetVelocity() { return m_Velocity; }
		bool IsKinematic() { return m_IsKinematic; }
		bool IsGrounded() { return m_IsGrounded; }

	private:
		TransformComponent* m_pTransform{};

		glm::vec2 m_Velocity{0.0f, 0.0f};
		glm::vec2 m_DisplayVelocity{};
		bool m_IsKinematic{ false };
		bool m_IsGrounded{ false };
	};

}
