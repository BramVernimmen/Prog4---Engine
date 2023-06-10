#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);

		void Update();
		void Render() const;
		void DisplayGui();

		void PreviousScene();
		void NextScene();

		Scene* GetActiveScene() { return m_pActiveScene; }
		void SetActiveScene(Scene* newActiveScene);

		void RemoveScene(std::shared_ptr<Scene> sceneToRemove);
		void AddScene(std::shared_ptr<Scene> sceneToAdd);

		std::vector<std::shared_ptr<Scene>>& GetScenes() { return m_scenes; }

	private:
		void KnownSetActiveScene(Scene* newActiveScene);

		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		Scene* m_pActiveScene{nullptr};
	};
}
