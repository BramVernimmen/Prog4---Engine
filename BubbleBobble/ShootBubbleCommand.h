#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;
	class PlayerComponent;
	class ShootBubbleCommand : public Command
	{
	public:
		ShootBubbleCommand(GameObject* pGameObject, unsigned short shootId, float shootForce = 200.0f);
		~ShootBubbleCommand() = default;

		ShootBubbleCommand(const ShootBubbleCommand& other) = delete;
		ShootBubbleCommand(ShootBubbleCommand&& other) = delete;
		ShootBubbleCommand& operator=(const ShootBubbleCommand& other) = delete;
		ShootBubbleCommand& operator=(ShootBubbleCommand&& other) = delete;


		virtual void Execute() override;
	private:
		GameObject* m_pGameObject{};
		PlayerComponent* m_pPlayerComponent{};
		float m_ShootForce{100.0f};
		unsigned short m_ShootSoundId{};
	};

}
