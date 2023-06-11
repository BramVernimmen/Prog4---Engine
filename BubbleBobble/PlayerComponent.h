#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "Subject.h"
#include "GameEvents.h"

namespace dae
{
	class LivesComponent;
	class ScoreComponent;
	class PlayerComponent final : public UpdateComponent, public Subject, public Observer
	{
	public:
		PlayerComponent(GameObject* pOwner);
		~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;


		virtual void Update() override;

		void SetPlayerId(size_t newId) { m_PlayerId = newId; }
		size_t GetPlayerId() { return m_PlayerId; }

		virtual void Notify(const Event& currEvent, std::any payload = nullptr) override;

	private:
		size_t m_PlayerId{};
	};

}

