#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "Subject.h"

namespace dae
{
	class Scene final : public Subject
	{
		friend std::shared_ptr<Scene> SceneManager::CreateScene(const std::string& name);
	public:

		void Update();
		void Render() const;
		void DisplayGui();
		void CheckForRemoval();

		GameObject* GetRoot() { return m_pRoot.get(); }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void IsSetAsActive();

	private: 
		explicit Scene(const std::string& name);
		void RemoveMarkedObjects(GameObject* parent);

		std::string m_name;
		std::unique_ptr<GameObject> m_pRoot;

		static unsigned int m_idCounter; 
	};

}
