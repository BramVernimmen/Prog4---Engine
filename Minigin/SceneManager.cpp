#include "SceneManager.h"
#include "Scene.h"
#include <stdexcept>

void dae::SceneManager::Update()
{
	m_pActiveScene->Update();
}

void dae::SceneManager::Render() const
{
	m_pActiveScene->Render();
}

void dae::SceneManager::DisplayGui()
{
	m_pActiveScene->DisplayGui();
}

void dae::SceneManager::CheckForRemoval()
{
	m_pActiveScene->CheckForRemoval();
}

void dae::SceneManager::PreviousScene()
{
	unsigned int numScenes{ static_cast<unsigned int>(m_scenes.size()) };
	for (unsigned int i = 0; i < numScenes; ++i)
	{
		// go through all scenes and check if the index is our current active scene
		if (m_scenes[i].get() == m_pActiveScene)
		{
			// if we have found the current active scene, we need to find the previous one
			if (i == 0) // check if the index is 0, then we need the amount of scenes - 1
			{
				i = numScenes; // if 0 set at amount of scenes
			}

			--i; // decrement to get the correct one

			KnownSetActiveScene(m_scenes[i].get());
			break;
		}
	}
}

void dae::SceneManager::NextScene()
{
	for (unsigned int i = 0; i < m_scenes.size(); ++i)
	{
		// go through all scenes and check if the index is our current active scene
		if (m_scenes[i].get() == m_pActiveScene) 
		{
			// if we have found the current active scene, we need to find the next one
			const unsigned int nextScene = ++i % m_scenes.size(); // increment index first, modulo size of scenes makes sure we loop back to 0
			KnownSetActiveScene(m_scenes[nextScene].get());
			break;
		}
	}
}

void dae::SceneManager::SetActiveScene(Scene* newActiveScene)
{
	// go through all scenes to check if the scene is in the manager
	for (auto it{ m_scenes.begin() }; it != m_scenes.end(); ++it)
	{
		if ((*it).get() == newActiveScene)
		{
			KnownSetActiveScene(newActiveScene);
			return;
		}
	}

	throw std::runtime_error(std::string("This scene is not in the SceneManager."));
}

void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> sceneToRemove)
{
	if (sceneToRemove.get() == m_pActiveScene)
	{
		throw std::runtime_error(std::string("Cannot remove current active scene"));
		// removing the current active scene could give massive problems
		// better to throw an error
	}

	for (auto it{ m_scenes.begin() }; it != m_scenes.end(); ++it)
	{
		if ((*it) == sceneToRemove)
		{
			m_scenes.erase(it);
			return;
		}
	}
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> sceneToAdd)
{
	for (auto it{ m_scenes.begin() }; it != m_scenes.end(); ++it)
	{
		if ((*it) == sceneToAdd)
		{
			// if we find the same scene, just return -> this scene is already in the manager
			// no need to throw an error for this
			return;
		}
	}

	m_scenes.push_back(sceneToAdd);
}

void dae::SceneManager::KnownSetActiveScene(Scene* newActiveScene)
{
	// this function will straight up set the active scene, without any checks
	// because this is powerful and can easily break stuff, it is private
	m_pActiveScene = newActiveScene;
	m_pActiveScene->IsSetAsActive();
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);

	if (m_pActiveScene == nullptr)
	{
		KnownSetActiveScene(scene.get());
	}

	return scene;
}
