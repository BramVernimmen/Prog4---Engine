#include "RotatorComponent.h"
#include "Time.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_TransformComponent = GetOwner()->GetComponent<TransformComponent>().get();
}

void dae::RotatorComponent::Update()
{
	m_Rotation += Time::GetInstance().GetDeltaTime() * m_Speed;

	if (m_Rotation >= m_TwoPi) // reset, this will avoid overflows (that will probably rarely happen)
		m_Rotation -= m_TwoPi;

	m_RotationResults.x = cosf(m_Rotation) * m_Radius;
	m_RotationResults.y = sinf(m_Rotation) * m_Radius;


	if (m_TrackingTransformComponent) // if we have something to track
	{
		//cache the locked
		const auto& localPosOfTracker{ m_TrackingTransformComponent->GetLocalPosition() };
		// add that local position to our rotation results
		m_RotationResults.x += localPosOfTracker.x;
		m_RotationResults.y += localPosOfTracker.y;
	}

	// rotate
	m_TransformComponent->SetLocalPosition(m_RotationResults.x + m_Offset.x, m_RotationResults.y + m_Offset.y);

}

void dae::RotatorComponent::SetTracking(TransformComponent* transToTrack)
{
	m_TrackingTransformComponent = transToTrack;
}
