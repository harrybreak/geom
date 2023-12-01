#pragma once

#include <vector>

#include "Object.hpp"
#include "SDL_render.h"
#include "Types.hpp"
#include <glm/glm.hpp>

/**
 * A scene is a list of drawable objects.
 */
class Scene : public std::vector<Object*>
{
	public:
		void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);
};
