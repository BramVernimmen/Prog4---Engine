#pragma once
#include "UpdateComponent.h"
#include <string>
#include <vector>

namespace dae
{

	class EndMenuComponent final : public UpdateComponent
	{
	public:
		EndMenuComponent(GameObject* pOwner);
		~EndMenuComponent() = default;
		EndMenuComponent(const EndMenuComponent& other) = delete;
		EndMenuComponent(EndMenuComponent&& other) = delete;
		EndMenuComponent& operator=(const EndMenuComponent& other) = delete;
		EndMenuComponent& operator=(EndMenuComponent&& other) = delete;

		virtual void Update() override {};
		virtual void DisplayGui() override;

		void SetHighScoreFilePath(const std::string& filePath); 
	private:
		void ReadHighscoreFile();
		std::vector<std::string> m_HighscoreInitials{};
		std::vector<int> m_Highscores{};

		void WriteHighscoreToFile(int score = 192, const std::string& initials = "PRO");

		std::string m_HighScoreFilePath{};
		std::string m_CurrentInitialsString{};
		int m_CurrentScore{ 0 };

		size_t m_MaxAmountOfScoresSaved{ 10 };
	};

}
