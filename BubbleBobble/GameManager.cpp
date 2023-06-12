#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EndMenuComponent.h"
#include "PlayerManager.h"

void dae::GameManager::Notify(const Event& currEvent, std::any payload)
{
	if (typeid(currEvent) == typeid(SceneLoaded))
	{
		if (payload.type() == typeid(Scene*))
		{
			auto endMenuComps{ std::any_cast<Scene*>(payload)->GetRoot()->GetComponentsInChildren<EndMenuComponent>() };
			if (!endMenuComps.empty())
			{
				endMenuComps.front()->SetCurrentScore(m_CurrentMaxScore);
				m_CurrentMaxScore = 0;
			}
		}
	}

}

void dae::GameManager::AllPlayersDead()
{
	m_CurrentMaxScore = PlayerManager::GetInstance().GetHighestScore();
	SceneManager::GetInstance().SetActiveScene(m_pEndScene);
}

void dae::GameManager::AllEnemiesDead()
{
	SceneManager::GetInstance().NextScene();
}
