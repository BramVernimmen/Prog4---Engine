#include "GridComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Utils_SDL.h"
#include "TextureComponent.h"
#include "BoxCollision.h"
#include "PlayerSpawnComponent.h"
#include "EnemySpawnComponent.h"

dae::GridComponent::GridComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	m_pTransform = GetOwner()->GetComponent<TransformComponent>();
}

void dae::GridComponent::Render() const
{
	// only for debug purposes
	const auto& worldPos = m_pTransform->GetWorldPosition();
	glm::vec2 pos{ worldPos.x, worldPos.y };

	EngineUtils::SetDrawColor(0, 255, 0, 255);

	for (int i = 0; i < m_Width; ++i) // for each width
	{
		for (int j = 0; j < m_Height; ++j)
		{
			glm::vec2 currentPos{};
			currentPos.x = pos.x + (i * static_cast<float>(m_PixelSize));
			currentPos.y = pos.y + (j * static_cast<float>(m_PixelSize));

			EngineUtils::DrawRect(currentPos, m_PixelSize, m_PixelSize);

		}
	}

}

void dae::GridComponent::Resize(int newWidth, int newHeight)
{
	m_Width = newWidth;
	m_Height = newHeight;

	CreateTiles();
}

void dae::GridComponent::CreateTiles()
{

	dae::GameObject* parent = GetOwner();
	dae::TextureComponent* textureComp = parent->GetComponent<dae::TextureComponent>();
	const auto& pTileTexture = textureComp->GetTexture();
	dae::RenderComponent* renderComp = parent->GetComponent<dae::RenderComponent>();

	const auto& worldPos = m_pTransform->GetWorldPosition();
	glm::vec2 pos{ worldPos.x, worldPos.y };

	constexpr uint32_t boxLayer{ 0b1 }; boxLayer;
	constexpr uint32_t platformLayer{ 0b10 }; platformLayer;

	for (int i = 0; i < m_Width; ++i) // for each width
	{
		for (int j = 0; j < m_Height; ++j)
		{
			int currentIndex{ i + (j * m_Width) };
			if (m_TileLayout[currentIndex] == '-')
				continue;


			glm::vec2 currentPos{};
			currentPos.x = (i * static_cast<float>(m_PixelSize));
			currentPos.y = (j * static_cast<float>(m_PixelSize));

			if (m_TileLayout[currentIndex] == 'P')
			{
				auto spawn{ parent->AddComponent<PlayerSpawnComponent>() };
				spawn->SetSpawnPosition(pos.x + currentPos.x,pos.y + currentPos.y);
				continue;
			}
			else if (m_TileLayout[currentIndex] == 'E')
			{
				auto spawn{ parent->AddComponent<EnemySpawnComponent>() };
				spawn->SetSpawnPosition(pos.x + currentPos.x, pos.y + currentPos.y);
				continue;
			}


			uint32_t currentLayer{ 0b0 };
			if (m_TileLayout[currentIndex] == 'X')
			{
				currentLayer = boxLayer;
			}
			else if (m_TileLayout[currentIndex] == '|')
			{
				currentLayer = platformLayer;
			}


			dae::GameObject* tile = new dae::GameObject();
			tile->SetParent(parent);
			auto transComp = tile->GetComponent<dae::TransformComponent>();
			transComp->SetLocalPosition(currentPos.x, currentPos.y);
			renderComp->AddTextureToRender(pTileTexture.get(), transComp);

			// give every tile a BoxCollision
			auto collision = tile->AddComponent<dae::BoxCollision>();
			collision->SetSize(m_PixelSize, m_PixelSize);
			collision->SetStatic();
			collision->SetCurrentLayer(currentLayer);
			renderComp->AddToDebug(collision);

		}
	}
}
