#include "MainMenuComponent.h"
#include "imgui.h"
#include "SceneManager.h"
#include "PlayerManager.h"

dae::MainMenuComponent::MainMenuComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::MainMenuComponent::DisplayGui()
{
    ImGui::Begin("Main Menu");

    if (ImGui::Button("1 Player"))
    {
        PlayerManager::GetInstance().SetPlayerCount(1);
        SceneManager::GetInstance().NextScene();
    }
    
    if (ImGui::Button("2 Players"))
    {
        PlayerManager::GetInstance().SetPlayerCount(2);
        SceneManager::GetInstance().NextScene();
    }

    ImGui::Button("Versus -- NOT IMPLEMENTED");

    ImGui::End();
}
