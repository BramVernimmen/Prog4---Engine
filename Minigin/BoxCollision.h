#pragma once
#include "UpdateComponent.h"
#include "Subject.h"
#include <SDL_rect.h>


namespace dae
{
	class TransformComponent;
	class BoxCollision final : public UpdateComponent, public Subject
	{
	public:
		BoxCollision(GameObject* pOwner);
		~BoxCollision();
		BoxCollision(const BoxCollision& other) = delete;
		BoxCollision(BoxCollision&& other) = delete;
		BoxCollision& operator=(const BoxCollision& other) = delete;
		BoxCollision& operator=(BoxCollision&& other) = delete;


		virtual void Update() override {};
		virtual void Render() const override; // for debug only

		void SetSize(int width, int height);

		SDL_Rect GetRect();

		// static BoxColliders will not get updated
		void SetStatic() { m_IsStatic = true; }
		void SetDynamic() { m_IsStatic = false; }

		bool IsStatic() { return m_IsStatic; }
		void SetCurrentLayer(uint32_t newLayer) { m_CurrentLayer = newLayer; }
		uint32_t GetLayer() { return m_CurrentLayer; }

		void AddIgnoreLayer(uint32_t newIgnoreLayer) { m_IgnoreLayers |= newIgnoreLayer; }
		void RemoveIgnoreLayer(uint32_t newRemoveIgnoreLayer) { m_IgnoreLayers &= (~newRemoveIgnoreLayer); }
		uint32_t GetIgnoreLayers() { return m_IgnoreLayers; }

		
		void AddLayerForOverlapEvent(uint32_t newOverlapLayer) { m_LayersToTriggerOverlapEvent |= newOverlapLayer; }
		void RemoveLayerForOverlapEvent(uint32_t newRemoveOverlapLayer) { m_LayersToTriggerOverlapEvent &= (~newRemoveOverlapLayer); }
		uint32_t GetOverlapEventLayers() { return m_LayersToTriggerOverlapEvent; }
		void IsOverlappingWith(GameObject* overlappingGameObject);

		void SetInactive() { m_IsActive = false; }
		void SetActive() { m_IsActive = true; }
		bool IsActive() { return m_IsActive; }

	private:
		TransformComponent* m_pTransform{}; // top left
		int m_Width{ 5 };
		int m_Height{ 5 };
		bool m_IsStatic{ false };
		bool m_IsActive{ true };

		uint32_t m_CurrentLayer{ 0b0 }; // put everything on layer 0
		uint32_t m_IgnoreLayers{ 0b0 };
		uint32_t m_LayersToTriggerOverlapEvent{ 0b0 };
	};

}
