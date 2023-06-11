#pragma once
namespace dae
{
	class GameObject;
	class EnemyState
	{
	public:
		virtual ~EnemyState() = default;
		virtual void OnEnter() = 0;
		virtual void Update() = 0;
		virtual void OnExit() = 0;

	protected:
		GameObject* m_pEnemy{ };
	};

}