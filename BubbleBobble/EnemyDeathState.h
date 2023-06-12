#pragma once
#include "EnemyState.h"
#include "Texture2D.h"
#include <memory>

namespace dae
{
	class GameObject;
	class RenderComponent;
	class EnemyDeathState final : public EnemyState
	{
	public:
		EnemyDeathState(GameObject* pEnemy);
		~EnemyDeathState() = default;

		EnemyDeathState(const EnemyDeathState& other) = delete;
		EnemyDeathState(EnemyDeathState&& other) = delete;
		EnemyDeathState& operator=(const EnemyDeathState& other) = delete;
		EnemyDeathState& operator=(EnemyDeathState&& other) = delete;

		virtual void OnEnter() override;
		virtual void Update() override {}
		virtual void OnExit() override {}

		void SetTexture(std::shared_ptr<Texture2D> newTexture);
		void SetDeathSoundId(unsigned short id) { m_DeathSoundId = id; }
	private:
		std::shared_ptr<Texture2D> m_pDeathTexture{};
		RenderComponent* m_pRenderComp{};
		unsigned short m_DeathSoundId{};
	};

}