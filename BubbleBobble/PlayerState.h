#pragma once
#include <any>
namespace dae
{
	class GameObject;
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;
		virtual void OnEnter() = 0;
		virtual void Update() = 0;
		virtual void OnExit() = 0;
		virtual void HandleInput(std::any payload) = 0;

	protected:
		GameObject* m_pPlayer{ };
	};

}