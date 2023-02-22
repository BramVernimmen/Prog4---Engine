#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:

		virtual void Update() = 0;
		virtual void Render() const {}

		BaseComponent(std::shared_ptr<GameObject>& pParent);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	private:
		std::weak_ptr<GameObject> m_GameObject;
	};
}


