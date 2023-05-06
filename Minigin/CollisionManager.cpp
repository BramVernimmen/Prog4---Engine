#include "CollisionManager.h"
#include "BoxCollision.h"
#include <iostream>
#include "TransformComponent.h"
#include "GameObject.h"
#include "RigidBody.h"

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
		const int amountOfHits{ static_cast<int>(hitRects.size()) };

		if (amountOfHits > 0) // we have a hit
		{
			const SDL_Rect& currBox = currBoxCollision->GetRect();
			dae::TransformComponent* pTransform = currBoxCollision->GetOwner()->GetComponent<dae::TransformComponent>();
			


			int totalOffsetX{ 0 };
			int totalOffsetY{ 0 };

			// we want to figure out how many collisions happen and where they actually are
			int amountOfRights{ 0 };
			int amountOfBelow{ 0 };

			for (const auto& hit : hitRects)
			{


				bool currIsLeft{ currBox.x <= hit.x };
				bool currIsAbove{ currBox.y <= hit.y };

				int offsetX{ 0 };
				int offsetY{ 0 };

				if (currIsLeft)
				{
					offsetX = hit.x - (currBox.x + currBox.w);
					amountOfRights++;
				}
				else
				{
					offsetX = (currBox.x - (hit.x + hit.w)) * -1;
				}

				if (currIsAbove)
				{
					offsetY = hit.y - (currBox.y + currBox.h);
					amountOfBelow++;
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

			totalOffsetX /= amountOfHits;
			totalOffsetY /= amountOfHits;

			glm::vec2 localPos = pTransform->GetLocalPosition();

			dae::RigidBody* rigid = currBoxCollision->GetOwner()->GetComponent<dae::RigidBody>();
			// only if we have a rigidbody

			if (rigid != nullptr)
			{
				// get velocity
				glm::vec2 currVelocity{ rigid->GetVelocity() };



				if ((amountOfBelow == amountOfHits || (amountOfBelow >= amountOfRights && amountOfRights > 0)) && amountOfHits > 1 && amountOfHits < 6 && !rigid->IsGrounded())
				{
					currVelocity.y = 0.0f;
					rigid->SetGrounded();
				}
				else if (amountOfHits == 6 && currVelocity.y < 0 && amountOfBelow > 3)
				{
					currVelocity.y = 0.0f;
					rigid->SetGrounded();
				}
				else if (amountOfBelow == amountOfHits && amountOfHits == 1 && (currBox.y + currBox.w - 2 < hitRects.front().y))
				{
					// check if we are 2 pixels away from the edge or not
					int difference{ 0 };
					if (amountOfRights == 1)
					{
						// 1 block to the right
						difference = hitRects.front().x - (currBox.x + currBox.w);
					}
					else
					{
						// 1 block to the left
						difference = currBox.x - (hitRects.front().x + hitRects.front().w);
					}

					if (abs(difference) > 2)
					{
						currVelocity.y = 0.0f;
						rigid->SetGrounded();
					}
				}
				
				if ((amountOfBelow == 0 || amountOfHits == 6) && currVelocity.y >= 0.0f && !rigid->IsGrounded())
				{
					currVelocity.y = 0.0f;
				}


				// make sure we stop moving when hitting the lowest side of a tile, while keep moving if we are higher up.
				if (rigid->IsGrounded() || (amountOfHits == 1 && amountOfBelow == 0 && (currBox.y < hitRects.front().y + hitRects.front().w - 1)))
				{
					currVelocity.x = 0.0f;
				}


				// set velocity
				rigid->SetVelocity(currVelocity);
			}
			

			pTransform->SetLocalPosition(localPos.x + totalOffsetX, localPos.y + totalOffsetY);

		}
		else
		{
			// check if it has a rigidbody
			// if so set grounded to false
			dae::RigidBody* rigid = currBoxCollision->GetOwner()->GetComponent<dae::RigidBody>();
			if (rigid == nullptr)
				break;

			rigid->SetGrounded(false);

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
