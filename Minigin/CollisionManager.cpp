#include "CollisionManager.h"
#include "BoxCollision.h"
#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"

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

std::vector<SDL_Rect> dae::CollisionManager::GetColliding(dae::BoxCollision* collisionToCheck)
{
	std::vector<SDL_Rect> hitRects{};

	const SDL_Rect& boxToCheck = collisionToCheck->GetRect();
	for (const auto& box : m_pBoxCollisions)
	{
		if (box == collisionToCheck)
			continue;

		if (IsOverlapping(boxToCheck, box->GetRect()))
		{
			//hitRect = box->GetRect();
			//std::cout << "HIT\n";
			hitRects.emplace_back(box->GetRect());
		}
	}

	return hitRects;

}

void dae::CollisionManager::Update()
{
	for (const auto& currBoxCollision : m_pBoxCollisions)
	{
		if (currBoxCollision->IsStatic())
			continue;



		const auto& hitRects = GetColliding(currBoxCollision);
		if (hitRects.size() > 0) // we have a hit
		{
			const SDL_Rect& currBox = currBoxCollision->GetRect();
			dae::TransformComponent* pTransform = currBoxCollision->GetOwner()->GetComponent<dae::TransformComponent>();
			


			int totalOffsetX{ 0 };
			int totalOffsetY{ 0 };

			for (const auto& hit : hitRects)
			{


				bool currIsLeft{ currBox.x <= hit.x };
				bool currIsAbove{ currBox.y <= hit.y };

				int offsetX{ 0 };
				int offsetY{ 0 };

				if (currIsLeft)
				{
					offsetX = hit.x - (currBox.x + currBox.w);
				}
				else
				{
					offsetX = (currBox.x - (hit.x + hit.w)) * -1;
				}

				if (currIsAbove)
				{
					offsetY = hit.y - (currBox.y + currBox.h);
				}
				else
				{
					offsetY = (currBox.y - (hit.y + hit.h)) * -1;
				}



				if (abs(offsetX) < abs(offsetY))
				{
					offsetY = 0;
				}
				else if (abs(offsetX) > abs(offsetY))
				{
					offsetX = 0;
				}
				totalOffsetX += offsetX;
				totalOffsetY += offsetY;


			}

			totalOffsetX /= static_cast<int>(hitRects.size());
			totalOffsetY /= static_cast<int>(hitRects.size());

			glm::vec2 localPos = pTransform->GetLocalPosition();

			pTransform->SetLocalPosition(localPos.x + totalOffsetX, localPos.y + totalOffsetY);

		}
		
	}

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
