#pragma once
#include "Axis2DCommand.h"
#include <memory>
#include <string>

namespace dae
{
	class GameObject;
	//class TransformComponent;
	class RigidBody;
	class MoveCommand final : public Axis2DCommand
	{
	public:
		MoveCommand(GameObject* pGameObject, float speed, float jumpStrength, unsigned short jumpSoundID, const std::string& jumpSoundPath);
		~MoveCommand() = default;
		
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;


		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		//TransformComponent* m_pTransform{};
		RigidBody* m_pRigidBody{};
		float m_MovementSpeed{};
		float m_JumpStrength{};
		unsigned short m_JumpSoundID{};
	};

}

