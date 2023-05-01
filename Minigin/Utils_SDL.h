#pragma once
#include <glm/glm.hpp>
#include <SDL.h>
#include "Renderer.h"

namespace EngineUtils
{
	inline void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
	{
		auto& renderer = dae::Renderer::GetInstance();
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), r, g, b, a);
	}
	inline void SetDrawColor(const SDL_Color& newColor)
	{
		SetDrawColor(newColor.r, newColor.g, newColor.b, newColor.a);
	}



	inline void DrawLine(int x1, int y1, int x2, int y2)
	{
		auto& renderer = dae::Renderer::GetInstance();
		SDL_RenderDrawLine(renderer.GetSDLRenderer(), x1, y1, x2, y2);
	}

	inline void DrawRect(const SDL_Rect& rect)
	{
		auto& renderer = dae::Renderer::GetInstance();
		SDL_RenderDrawRect(renderer.GetSDLRenderer(), &rect);
	}
	inline void DrawRect(const glm::vec2& topLeft, int width, int height)
	{
		SDL_Rect rect{};

		rect.x = static_cast<int>(topLeft.x);
		rect.y = static_cast<int>(topLeft.y);
		rect.w = width;
		rect.h = height;
		DrawRect(rect);
	}



}

