#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "BaseComponent.h"
#include "RenderComponent.h"

namespace dae
{
	//class RenderComponent;
	// has to be public: https://stackoverflow.com/questions/56415222/why-weak-from-this-always-returns-empty-weak-pointer
	class GameObject final
	{
	public:
		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;
		void DisplayGui();


		template <typename T> T* AddComponent();
		template <typename T> T* GetComponent() const;
		template <typename T> std::vector<T*> GetComponents() const;
		template <typename T> std::vector<T*> GetComponentsInChildren() const;
		template <typename T> void RemoveComponent();

		void SetParent(GameObject* newParent, bool keepWorldPosition = false);
		std::vector<GameObject*> GetChildren() const { return m_ReturnChildren; }
		GameObject* GetParent() const { return m_pParent; }
		GameObject* GetRootObject();

	protected:
		void AddChild(std::unique_ptr<GameObject> newChild);
		std::unique_ptr<GameObject> RemoveChild(GameObject* childToRemove);
		bool CheckIfChild(GameObject* parentToCheck);

	private:
		std::vector<std::unique_ptr<BaseComponent>> m_Components{};
		std::unique_ptr<BaseComponent> m_RenderComponent{};

		std::vector<std::unique_ptr<GameObject>> m_Children{};
		std::vector<GameObject*> m_ReturnChildren{};
		GameObject* m_pParent{};
	};



	template<typename T>
	inline T* GameObject::AddComponent()
	{
		if (std::is_base_of_v<T, RenderComponent>) // check if it is a render component
		{
			// check if it already exists, if so return that one
			if (m_RenderComponent)
				return dynamic_cast<T*>(m_RenderComponent.get());
			m_RenderComponent = std::make_unique<T>(this);

			return dynamic_cast<T*>(m_RenderComponent.get());
		}


		/// check not used anymore-> we want to have duplicate components on our objects
		// first check if a component already exists
		//if (T * checkComp{ GetComponent<T>() }) 
		//	return checkComp;


		// if we get here, the component doesn't exist yet, create it
		m_Components.push_back(std::make_unique<T>(this));
		return dynamic_cast<T*>(m_Components.back().get()); // return the last element, this is the one we just added
	}


	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		if (T* castedComp = dynamic_cast<T*>(m_RenderComponent.get()))
			return castedComp;

		for (const auto& currComponent : m_Components)
		{
			T* castedComp = dynamic_cast<T*>(currComponent.get());
			if (castedComp)
				return castedComp;
		}
		return nullptr; // nothing found
	}

	template<typename T>
	inline std::vector<T*> GameObject::GetComponents() const
	{
		std::vector<T*> componentsToReturn{};

		for (const auto& currComponent : m_Components)
		{
			T* castedComp = dynamic_cast<T*>(currComponent.get());
			if (castedComp)
				componentsToReturn.emplace_back(castedComp);
		}

		return componentsToReturn;
	}

	template<typename T>
	inline std::vector<T*> GameObject::GetComponentsInChildren() const
	{
		std::vector<T*> componentsToReturn{};
		for (const auto& currChild : m_Children)
		{
			std::vector<T*> components{ currChild->GetComponents<T>() };
			componentsToReturn.insert(componentsToReturn.end(), components.begin(), components.end());
			std::vector<T*> childComponents{ currChild->GetComponentsInChildren<T>() };
			componentsToReturn.insert(componentsToReturn.end(), childComponents.begin(), childComponents.end());
			
		}
		return componentsToReturn;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		// removing the first component
		for (auto it{ m_Components.begin() }; it != m_Components.end(); ++it)
		{
			T* castedComp = dynamic_cast<T*>((*it).get());
			if (castedComp)
			{
				m_Components.erase(it);
				return;
			}
		}
		
	}
}
