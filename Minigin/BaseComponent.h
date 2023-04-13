#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;


		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void DisplayGui() = 0;

	protected:
		GameObject* GetOwner() const { return m_pOwner.lock().get(); }

	private:
		std::weak_ptr<GameObject> m_pOwner;
	};
}


