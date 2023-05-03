#pragma once
#include <glm/glm.hpp>
#include <SDL_rect.h>

namespace EngineUtils
{
	inline bool IsPointInRect(glm::vec2 p, const SDL_Rect& r)
	{
		return (p.x >= r.x &&
			p.x <= r.x + r.w &&
			p.y >= r.y &&
			p.y <= r.y + r.h);
	}
}
