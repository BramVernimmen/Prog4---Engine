#pragma once
#include "Command.h"
#include <memory>
namespace dae
{
	class GameObject;
	class TransformComponent;
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(std::weak_ptr<GameObject> pGameObject, float speed);
		~MoveCommand() = default;
		
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;


		virtual void Execute() override;
	private:
		std::weak_ptr<GameObject> m_pGameObject{};
		std::weak_ptr<TransformComponent> m_pTransform{};
		float m_MovementSpeed{};
	};

}

