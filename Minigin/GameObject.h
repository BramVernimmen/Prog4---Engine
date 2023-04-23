#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

namespace dae
{
	class BaseComponent;
	class RenderComponent;
	// has to be public: https://stackoverflow.com/questions/56415222/why-weak-from-this-always-returns-empty-weak-pointer
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;
		void DisplayGui();


		template <typename T> std::shared_ptr<T> AddComponent();
		template <typename T> std::shared_ptr<T> GetComponent() const;
		template <typename T> void RemoveComponent();

		void SetParent(std::shared_ptr<GameObject> newParent);
		std::vector<std::shared_ptr<GameObject>> GetChildren() const { return m_Children; }
		std::weak_ptr<GameObject> GetParent() const { return m_pParent; }

	protected:
		void AddChild(std::shared_ptr<GameObject> newChild);
		void RemoveChild(std::shared_ptr<GameObject> childToRemove);
		bool CheckIfChild(std::shared_ptr<GameObject> parentToCheck);

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
		std::shared_ptr<BaseComponent> m_RenderComponent{};

		std::vector<std::shared_ptr<GameObject>> m_Children{};
		std::weak_ptr<GameObject> m_pParent{};
	};



	template<typename T>
	inline std::shared_ptr<T> GameObject::AddComponent()
	{
		if (std::is_base_of_v<T, RenderComponent>) // check if it is a render component
		{
			// check if it already exists, if so return that one
			if (m_RenderComponent)
				return std::dynamic_pointer_cast<T>(m_RenderComponent);
			m_RenderComponent = std::make_shared<T>(this);

			return std::dynamic_pointer_cast<T>(m_RenderComponent);
		}

		// first check if a component already exists
		for (const auto& currComponent : m_Components)
		{
			auto componentCheck{ std::dynamic_pointer_cast<T>(currComponent) };
			if (componentCheck) // if it does, return that one
				return componentCheck;
		}

		// if we get here, the component doesn't exist yet, create it
		m_Components.push_back(std::make_shared<T>(this));
		return std::dynamic_pointer_cast<T>(m_Components.back()); // return the last element, this is the one we just added
	}


	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (const auto& currComponent : m_Components)
		{
			std::shared_ptr<T> castedComp = std::dynamic_pointer_cast<T>(currComponent);
			if (castedComp)
				return castedComp;
		}
		return nullptr; // nothing found
	}
	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		// removing the first component
		for (auto it{ m_Components.begin() }; it != m_Components.end(); ++it)
		{
			std::shared_ptr<T> castedComp = std::dynamic_pointer_cast<T>(*it);
			if (castedComp)
			{
				m_Components.erase(it);
				return;
			}
		}

		
	}
}
