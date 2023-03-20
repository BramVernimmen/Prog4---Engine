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


	if (m_TrackingTransformComponent.expired() == false) // if we have something to track
	{
		//cache the locked
		const auto& lockedTracker{ m_TrackingTransformComponent.lock() };
		const auto& localPosOfTracker{ lockedTracker->GetLocalPosition() };
		// add that local position to our rotation results
		m_RotationResults.x += localPosOfTracker.x;
		m_RotationResults.y += localPosOfTracker.y;
	}

	// rotate
	m_TransformComponent.lock()->SetLocalPosition(m_RotationResults.x + m_Offset.x, m_RotationResults.y + m_Offset.y);

}

void dae::RotatorComponent::SetTracking(std::weak_ptr<TransformComponent> transToTrack)
{
	m_TrackingTransformComponent = transToTrack;
}
