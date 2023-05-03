#pragma once
#include "Singleton.h"
#include <vector>
#include <SDL_rect.h>

namespace dae
{
	class BoxCollision;
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddBoxCollision(dae::BoxCollision* collisionToAdd);
		void RemoveBoxCollision(dae::BoxCollision* collisionToRemove);
		std::vector<SDL_Rect> GetColliding(dae::BoxCollision* collisionToCheck);
		
		void Update();
	protected:

	private:
		bool IsOverlapping(const SDL_Rect& box1, const SDL_Rect& box2);

		std::vector<dae::BoxCollision*> m_pBoxCollisions{};
	};
}
