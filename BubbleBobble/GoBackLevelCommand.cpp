#include "GoBackLevelCommand.h"
#include "SceneManager.h"

void dae::GoBackLevelCommand::Execute()
{
	SceneManager::GetInstance().PreviousScene();
}
