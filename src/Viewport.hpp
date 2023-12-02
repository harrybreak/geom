#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#pragma once

#include <glm/glm.hpp>

class Viewport
{
public:

	static glm::vec3 TransformWorldToScreenSpace(glm::vec2 vertex, glm::mat3 projectionTransform)
	{
		return projectionTransform * glm::vec3(vertex.x, vertex.y, 1);
	}

	static glm::vec2 TransformScreenSpaceToWorld(glm::vec2 screenVertex, glm::mat3 projectionTransform)
	{
		// Invert the projection transform
		glm::mat3 inverseProjectionTransform = glm::inverse(projectionTransform);

		// Transform the screen vertex back to world space
		glm::vec3 worldVertex = inverseProjectionTransform * glm::vec3(screenVertex, 1);

		// Return the result as a 2D vector
		return glm::vec2(worldVertex.x, worldVertex.y);
	}
};