#include "SkipLevelCommand.h"
#include "SceneManager.h"

void dae::SkipLevelCommand::Execute()
{
	SceneManager::GetInstance().NextScene();
}
