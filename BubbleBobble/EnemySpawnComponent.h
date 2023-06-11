#pragma once
#include "UpdateComponent.h"
#include <glm/glm.hpp>
namespace dae
{
	class TransformComponent;

	class EnemySpawnComponent final : public UpdateComponent
	{
	public:
		EnemySpawnComponent(GameObject* pOwner);
		~EnemySpawnComponent() = default;
		EnemySpawnComponent(const EnemySpawnComponent& other) = delete;
		EnemySpawnComponent(EnemySpawnComponent&& other) = delete;
		EnemySpawnComponent& operator=(const EnemySpawnComponent& other) = delete;
		EnemySpawnComponent& operator=(EnemySpawnComponent&& other) = delete;


		virtual void Update() override {};
		void SetSpawnPosition(float x, float y);
		glm::vec2 GetSpawnPosition() { return m_SpawnPosition; }

	private:
		glm::vec2 m_SpawnPosition{};

	};
}
