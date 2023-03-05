#include "RotatorComponent.h"
#include "Time.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(std::weak_ptr<GameObject> pOwner)
	: UpdateComponent(pOwner)
{
	m_TransformComponent = pOwner.lock()->GetComponent<TransformComponent>();
}

void dae::RotatorComponent::Update()
{
	m_Rotation += Time::GetInstance().GetDeltaTime() * m_Speed;

	if (m_Rotation >= m_TwoPi) // reset, this will avoid overflows (that will probably rarely happen)
		m_Rotation -= m_TwoPi;

	m_RotationResults.x = cosf(m_Rotation) * m_Radius;
	m_RotationResults.y = sinf(m_Rotation) * m_Radius;


	// we seperate the ones that will be tracking
	// if we are trackign a certain position, we will overwrite the worldposition
	// if we don't, we aren't circling around the position if we have a parent, we will be offset
	// if we want an offset, we can always set our offset for the rotator
	if (m_TrackingTransformComponent.expired() == false) // if we have something to track
	{
		//cache the locked
		const auto& lockedTracker{ m_TrackingTransformComponent.lock() };
		const auto& worldPosOfTracker{ lockedTracker->GetWorldPosition() };
		// add that world position to our rotation results
		m_RotationResults.x += worldPosOfTracker.x;
		m_RotationResults.y += worldPosOfTracker.y;
		m_TransformComponent.lock()->SetWorldPosition({ m_RotationResults.x + m_Offset.x, m_RotationResults.y + m_Offset.y , 0.0f});
	}
	else
	{
		m_TransformComponent.lock()->SetLocalPosition(m_RotationResults.x + m_Offset.x, m_RotationResults.y + m_Offset.y);
	}

}

void dae::RotatorComponent::SetTracking(std::weak_ptr<TransformComponent> transToTrack)
{
	m_TrackingTransformComponent = transToTrack;
}
