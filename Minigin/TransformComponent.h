#pragma once
#include <glm/glm.hpp>
#include "UpdateComponent.h"

namespace dae
{
	class TransformComponent final : public UpdateComponent
	{
	public:
		TransformComponent(std::weak_ptr<GameObject> pOwner);
		~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;


		virtual void Update() override;

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition() const;
		void SetLocalPosition(float x, float y);
		void SetWorldPosition(glm::vec3 newWorldPos);

		void SetDirty();

	private:

		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};

		bool m_NeedsUpdate{ false };

	};
}
