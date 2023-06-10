#include "LevelLoaderComponent.h"
#include "ResourceManager.h"
#include <fstream>
#include "GridComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"

dae::LevelLoaderComponent::LevelLoaderComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::LevelLoaderComponent::AddLevelFile(const std::string& fileName)
{
	m_FileNames.emplace_back(fileName);
}

void dae::LevelLoaderComponent::SetGridOffset(float x, float y)
{
	m_GridOffset.x = x;
	m_GridOffset.y = y;
}

void dae::LevelLoaderComponent::SetGridSize(int x, int y)
{
	m_GridSizeX = x;
	m_GridSizeY = y;
}

void dae::LevelLoaderComponent::CreateLevels()
{
	for (const std::string& currPath : m_FileNames)
	{
		// open the level and read it
		std::string filePath{dae::ResourceManager::GetInstance().GetDataPath()};
		filePath += currPath; // best way to concatenate strings (according to stackoverflow benchmark; https://stackoverflow.com/questions/18892281/most-optimized-way-of-concatenation-in-strings )
		if (std::ifstream input{filePath})
		{
			// get the ID
			std::string id{};
			std::getline(input, id);

			std::string tileTexturePath{dae::ResourceManager::GetInstance().GetDataPath()};
			tileTexturePath += m_TileTextureLocation;
			tileTexturePath += id;
			tileTexturePath += m_TileTextureExtension;


			// put the tile layout in a string
			std::string levelLayout{};
			while (!input.eof())
			{
				std::string readResult{};
				std::getline(input, readResult);

				levelLayout += readResult;
			}


			// create a new level
			auto newLevel = dae::SceneManager::GetInstance().CreateScene("Level_" + id);
			dae::GameObject* pLevelRoot = newLevel->GetRoot();

			// spawn the grid on that level
			GameObject* grid = new GameObject();
			grid->SetParent(pLevelRoot);
			auto renderComp = grid->AddComponent<dae::RenderComponent>();
			auto gridComp = grid->AddComponent<dae::GridComponent>();
			renderComp->AddToDebug(gridComp);
			auto transComp = grid->GetComponent<dae::TransformComponent>();
			auto textureComp = grid->AddComponent<dae::TextureComponent>();
			textureComp->SetTexture(tileTexturePath);
			gridComp->SetTileLayout(levelLayout);
			transComp->SetLocalPosition(m_GridOffset.x, m_GridOffset.y);
			gridComp->Resize(m_GridSizeX, m_GridSizeY); // resize will create the tile layout
		}
		

	}
}
