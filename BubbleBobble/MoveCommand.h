#pragma once
#include "Axis2DCommand.h"
#include <memory>
namespace dae
{
	class GameObject;
	class TransformComponent;
	class BoxCollision;
	class MoveCommand final : public Axis2DCommand
	{
	public:
		MoveCommand(GameObject* pGameObject, float speed);
		~MoveCommand() = default;
		
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;


		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		TransformComponent* m_pTransform{};
		float m_MovementSpeed{};
	};

}

