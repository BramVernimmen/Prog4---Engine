#pragma once
#include "UpdateComponent.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace dae
{
	class LevelLoaderComponent final : public UpdateComponent
	{
	public:
		LevelLoaderComponent(GameObject* pOwner);
		~LevelLoaderComponent() = default;
		LevelLoaderComponent(const LevelLoaderComponent& other) = delete;
		LevelLoaderComponent(LevelLoaderComponent&& other) = delete;
		LevelLoaderComponent& operator=(const LevelLoaderComponent& other) = delete;
		LevelLoaderComponent& operator=(LevelLoaderComponent&& other) = delete;


		virtual void Update() override {};

		void AddLevelFile(const std::string& fileName);
		void SetTileTextureLocation(const std::string& tileTextureLocation) { m_TileTextureLocation = tileTextureLocation; }
		void SetTileTextureExtension(const std::string& tileTextureExtension) { m_TileTextureExtension = tileTextureExtension; }
		void SetGridOffset(float x, float y);
		void SetGridSize(int x, int y);
		void CreateLevels();
	private:
		std::vector<std::string> m_FileNames{};

		// when loading in textures, we want to have the ID of the levels
		// this will look like e.g. 1, 2, 3
		// but for the texture we need e.g. 001, 002, 003
		// this will make us capable of fixing this; source: https://stackoverflow.com/questions/6143824/add-leading-zeroes-to-string-without-sprintf
		//size_t m_LeadingZeros{ 3 }; // gives support from 000 to 999
		// eventually didn't use this, yet still nice to know how

		glm::vec2 m_GridOffset{};
		
		std::string m_TileTextureLocation{};
		std::string m_TileTextureExtension{};

		int m_GridSizeX{};
		int m_GridSizeY{};
	};
}