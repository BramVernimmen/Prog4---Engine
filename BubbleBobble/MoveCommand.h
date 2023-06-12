#pragma once
#include "Axis2DCommand.h"

namespace dae
{
	class GameObject;
	class PlayerComponent;
	class MoveCommand final : public Axis2DCommand
	{
	public:
		MoveCommand(GameObject* pGameObject);
		~MoveCommand() = default;
		
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;


		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		PlayerComponent* m_pPlayerComponent{};
	};

}

