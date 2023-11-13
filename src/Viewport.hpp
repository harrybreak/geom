#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#pragma once

#include <glm/glm.hpp>

class Viewport
{
private:

public:

	static glm::vec3 TransformToScreenSpace(glm::vec2 vertex, glm::mat3 projectionTransform)
	{
		return projectionTransform * glm::vec3(vertex.x, vertex.y, 1);
	}
};