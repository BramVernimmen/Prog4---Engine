#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> pOwner)
	: m_pOwner{pOwner}
{
}
