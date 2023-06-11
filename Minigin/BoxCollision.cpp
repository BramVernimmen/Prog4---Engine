#include "BoxCollision.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Utils_SDL.h"
#include "CollisionManager.h"
#include "EngineEvents.h"

dae::BoxCollision::BoxCollision(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pTransform = GetOwner()->GetComponent<TransformComponent>();
	dae::CollisionManager::GetInstance().AddBoxCollision(this);
}

dae::BoxCollision::~BoxCollision()
{
	dae::CollisionManager::GetInstance().RemoveBoxCollision(this);
}

void dae::BoxCollision::Render() const
{
	EngineUtils::SetDrawColor(255, 0, 0, 255);

	const auto& worldPos = m_pTransform->GetWorldPosition();
	glm::vec2 currentPos{worldPos.x, worldPos.y};

	EngineUtils::DrawRect(currentPos, m_Width, m_Height);


}

void dae::BoxCollision::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

SDL_Rect dae::BoxCollision::GetRect()
{
	SDL_Rect rect{};
	const auto& worldPos = m_pTransform->GetWorldPosition();

	rect.x = static_cast<int>(worldPos.x);
	rect.y = static_cast<int>(worldPos.y);
	rect.w = m_Width;
	rect.h = m_Height;

	return rect;
}

void dae::BoxCollision::IsOverlappingWith(GameObject* overlappingGameObject)
{
	NotifyObservers(ObjectOverlapping(), overlappingGameObject);
}
