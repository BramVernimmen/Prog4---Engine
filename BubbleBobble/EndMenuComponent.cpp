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

    ImGui::Text("Current Highscores:");
    for (size_t i = 0; i < m_HighscoreInitials.size(); i++)
    {
        ImGui::Text("%i by: %s", m_Highscores[i], m_HighscoreInitials[i].c_str());
    }

    ImGui::Dummy(ImVec2(0.0f, 12.0f));
    // only show this when current score is higher then highscore
    ImGui::Text("Your Score: %i", m_CurrentScore);
    ImGui::Dummy(ImVec2(0.0f, 12.0f));

    if (m_Highscores.size() < m_MaxAmountOfScoresSaved || m_CurrentScore >= m_Highscores.back())
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
        ImGui::Text("Too bad, you didn't beat a highscore!");
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
        
        m_Highscores.clear();
        m_HighscoreInitials.clear();

        while (!input.eof())
        {
            // first line should be the score
            std::getline(input, currLine);
            m_Highscores.emplace_back(std::stoi(currLine));

            // second line should be the initials
            std::getline(input, currLine);
            m_HighscoreInitials.emplace_back(currLine);
        }
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
        if (m_Highscores.size() >= m_MaxAmountOfScoresSaved)
        {
            // this means we need to remove the lowest score
            m_Highscores.pop_back();
            m_HighscoreInitials.pop_back();
        }

        // go through all scores and check once the passed score is higher
        size_t i{ 0 };
        for (; i < m_Highscores.size(); ++i)
        {
            if (m_Highscores[i] <= score)
                break;
        }

        m_Highscores.insert(m_Highscores.begin() + i, score);
        m_HighscoreInitials.insert(m_HighscoreInitials.begin() + i, initials);

        for (size_t index = 0; index < m_Highscores.size(); ++index)
        {
            if (index > 0)
                output << "\n";
            output << m_Highscores[index];
            output << "\n";
            output << m_HighscoreInitials[index].c_str();
        }
    }
    

    
}
