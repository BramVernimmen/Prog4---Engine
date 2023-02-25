#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject>& pParent)
	: m_pGameObject{pParent}
{
}
