#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::weak_ptr<GameObject> pParent)
	: m_pGameObject{pParent}
{
}
