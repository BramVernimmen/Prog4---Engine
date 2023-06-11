#include "EndMenuComponent.h"
#include "imgui.h"
#include <fstream>
//#include <iostream>
#include "SceneManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"

dae::EndMenuComponent::EndMenuComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
    
}

void dae::EndMenuComponent::DisplayGui()
{
    ImGui::Begin("End Menu");

    ImGui::Text("Current Highscore: %i by: %s", m_Highscore, m_HighscoreInitials.c_str());
    ImGui::Dummy(ImVec2(0.0f, 12.0f));
    // only show this when current score is higher then highscore
    ImGui::Text("Your Score: %i", m_CurrentScore);
    ImGui::Dummy(ImVec2(0.0f, 12.0f));

    if (m_CurrentScore >= m_Highscore)
    {
        ImGui::PushItemWidth(30.0f);
        ImGui::InputText("Input Initials Here", &m_CurrentInitialsString[0], 4);
        ImGui::PopItemWidth();

        if (ImGui::Button("Save Score"))
        {
            //std::cout << "Score will be saved!\n";
            WriteHighscoreToFile(m_CurrentScore, m_CurrentInitialsString);
            m_CurrentInitialsString.clear();
            ReadHighscoreFile();
        }
    }
    else
    {
        ImGui::Text("Too bad, you didn't beat the highscore!");
    }
    
    ImGui::Dummy(ImVec2(0.0f, 25.0f));
    if (ImGui::Button("Back To Main Menu!"))
    {
        m_CurrentInitialsString.clear();
        PlayerManager::GetInstance().SetPlayerCount(0);
        SceneManager::GetInstance().NextScene(); // assuming that the main menu is the first scene and this is the last
    }


    ImGui::End();
}

void dae::EndMenuComponent::SetHighScoreFilePath(const std::string& filePath)
{
    m_HighScoreFilePath = filePath; 
    
    ReadHighscoreFile();
}

void dae::EndMenuComponent::ReadHighscoreFile()
{
    std::string filePath{dae::ResourceManager::GetInstance().GetDataPath()};
    filePath += m_HighScoreFilePath;

    if (std::ifstream input{filePath})
    {
        std::string currLine{};
        
        // first line should be the score
        std::getline(input, currLine);
        m_Highscore = std::stoi(currLine);

        // second line should be the initials
        std::getline(input, currLine);
        m_HighscoreInitials = currLine;
    }
    else
    {
        WriteHighscoreToFile();

        // after creating it, it has default values, so read those in
        ReadHighscoreFile();
    }

}

void dae::EndMenuComponent::WriteHighscoreToFile(int score, const std::string& initials)
{
    std::string filePath{dae::ResourceManager::GetInstance().GetDataPath()};
    filePath += m_HighScoreFilePath;

    // this will always overwrite the file with the new values
    if (std::ofstream output{filePath})
    {
        output << score;
        output << "\n";
        output << initials.c_str();
        output << "\n";
    }
    

    
}
