#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

namespace dae
{
	class Texture2D;
	class BaseComponent;

	class GameObject 
	{
	public:

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template <typename T> std::shared_ptr<T> AddComponent(std::shared_ptr<GameObject> go);
		template <typename T> std::shared_ptr<T> GetComponent() const;
		template <typename T> void RemoveComponent();


	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
	};



	template<typename T>
	inline std::shared_ptr<T> GameObject::AddComponent(std::shared_ptr<GameObject> go)
	{
		m_Components.push_back(std::make_shared<T>(go));
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
