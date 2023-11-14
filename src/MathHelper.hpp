#pragma once

#include <vector>

#include "Polygon.hpp"
#include "Types.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "Vertex.hpp"

void RRotate(glm::vec2* vertexCoordinates, glm::vec2 pivot, float angle)
{
	glm::mat4 translateToPivot = glm::translate(glm::mat4(1), glm::vec3(pivot, 1));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), glm::vec3(-pivot, 1));
	glm::mat4 finalTransformation = translateBack * rotationMatrix * translateToPivot;
	glm::vec4 transformedPosition = finalTransformation * glm::vec4(glm::vec3(*vertexCoordinates, 1.0f), 1.0f);
	*vertexCoordinates = glm::vec2(transformedPosition);
}

glm::vec2 ComputeCentroid(const std::vector<Vertex<float32>>& vertices)
{
	glm::vec2 sum(0.0f);

	for (const auto& vertex : vertices)
	{
		glm::vec2 vertexPosition(vertex.x, vertex.y);
		sum += vertexPosition;// + glm::vec2(-450, -150);
	}

	glm::vec2 centroid = sum / static_cast<float32>(vertices.size());

	return centroid;
}

float32 det(Vertex<float32> p, Vertex<float32> q, Vertex<float32> r)
{
	return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}