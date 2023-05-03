#pragma once
#include "UpdateComponent.h"
#include <SDL_rect.h>


namespace dae
{
	class TransformComponent;
	class BoxCollision final : public UpdateComponent
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

	private:
		TransformComponent* m_pTransform{}; // top left
		int m_Width{ 5 };
		int m_Height{ 5 };
		bool m_IsStatic{ false };
	};

}
