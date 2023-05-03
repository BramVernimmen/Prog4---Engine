#include "CollisionManager.h"
#include "BoxCollision.h"
#include <iostream>

void dae::CollisionManager::AddBoxCollision(dae::BoxCollision* collisionToAdd)
{
	auto foundIt = std::find_if(m_pBoxCollisions.begin(), m_pBoxCollisions.end(), [collisionToAdd](UpdateComponent* currElement)
		{ return currElement == collisionToAdd; });

	if (foundIt == m_pBoxCollisions.end()) // if we reach the end, add it
		m_pBoxCollisions.emplace_back(collisionToAdd);
}

void dae::CollisionManager::RemoveBoxCollision(dae::BoxCollision* collisionToRemove)
{
	auto foundIt = std::find_if(m_pBoxCollisions.begin(), m_pBoxCollisions.end(), [collisionToRemove](UpdateComponent* currElement)
		{ return currElement == collisionToRemove; });

	if (foundIt != m_pBoxCollisions.end()) // if we don't reach the end, remove it
		m_pBoxCollisions.erase(foundIt);
}

SDL_Rect dae::CollisionManager::CheckCollision(dae::BoxCollision* collisionToCheck)
{
	SDL_Rect hitRect{};
	hitRect.w = 0; // if we don't hit anything, return width as 0

	const SDL_Rect& boxToCheck = collisionToCheck->GetRect();
	for (const auto& box : m_pBoxCollisions)
	{
		if (box == collisionToCheck)
			continue;

		if (IsOverlapping(boxToCheck, box->GetRect()))
		{
			//hitRect = box->GetRect();
			//std::cout << "HIT\n";
			return box->GetRect();
		}
	}

	return hitRect;

}

bool dae::CollisionManager::IsOverlapping(const SDL_Rect& box1, const SDL_Rect& box2)
{
	// https://kishimotostudios.com/articles/aabb_collision/
	// quick and easy collision checking, no need for multiple if statements or anything

	bool AisToTheRightOfB = box1.x > (box2.x + box2.w);
	bool AisToTheLeftOfB = (box1.x + box1.w) < box2.x;
	bool AisBelowB = box1.y > (box2.y + box2.h);
	bool AisAboveB = (box1.y + box1.h) < box2.y;
	return !(AisToTheRightOfB || AisToTheLeftOfB || AisAboveB || AisBelowB);

}
