#pragma once
#include "UpdateComponent.h"
#include <glm/glm.hpp>
namespace dae
{
	class TransformComponent;

	class PlayerSpawnComponent final : public UpdateComponent
	{
	public:
		PlayerSpawnComponent(GameObject* pOwner);
		~PlayerSpawnComponent() = default;
		PlayerSpawnComponent(const PlayerSpawnComponent& other) = delete;
		PlayerSpawnComponent(PlayerSpawnComponent&& other) = delete;
		PlayerSpawnComponent& operator=(const PlayerSpawnComponent& other) = delete;
		PlayerSpawnComponent& operator=(PlayerSpawnComponent&& other) = delete;


		virtual void Update() override {};
		void SetSpawnPosition(float x, float y);
		glm::vec2 GetSpawnPosition() { return m_SpawnPosition; }

	private:
		glm::vec2 m_SpawnPosition{};

	};
}

