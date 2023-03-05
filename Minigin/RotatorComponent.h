#pragma once
#include "UpdateComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent;
	class RotatorComponent final : public UpdateComponent
	{
	public:
		RotatorComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;


		virtual void Update() override;
		void SetSpeed(float newSpeed) { m_Speed = newSpeed; }
		void SetRadius(float newRadius) { m_Radius = newRadius; }
		void SetOffset(glm::vec3 offset) { m_Offset = offset; }

		// setting the transform to rotate around
		void SetTracking(std::weak_ptr<TransformComponent> transToTrack);

	protected:

	private:
		std::weak_ptr<TransformComponent> m_TransformComponent{}; // this is the transform of our current Owner
		std::weak_ptr<TransformComponent> m_TrackingTransformComponent{}; // this is the transform of the Object we want to rotate around

		const float m_TwoPi{ 6.28318530718f };
		float m_Speed {5.0f};
		float m_Rotation{};
		float m_Radius{ 50.0f };
		glm::vec3 m_Offset{}; // original local position
		glm::vec3 m_RotationResults{ }; // tracks the offset that the rotation generates, this will set as local position later

	};

}

