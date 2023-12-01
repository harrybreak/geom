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

/**
 * RRotate(vertexCoordinates, pivot, angle):
 * compute and apply the 2D-rotation to 'vertexCoordinates'
 * with the angle 'angle' given in degrees /!\
 */
void RRotate(Vertex* vertexCoordinates, float angle)
{
	glm::mat4 translateToPivot = glm::translate(glm::mat4(1), glm::vec3(0, 0, 1));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1));
	glm::mat4 finalTransformation = translateBack * rotationMatrix * translateToPivot;
	glm::vec4 transformedPosition = finalTransformation * glm::vec4(glm::vec3(*vertexCoordinates, 1.0f), 1.0f);
	*vertexCoordinates = Vertex(transformedPosition);
}

/**
 * @deprecated
 * 
 * ComputeCentroid(array<Vertex> vertices) returns the centroid vector of the set 'vertices'
 */
Vertex ComputeCentroid(const std::vector<Vertex>& vertices)
{
	Vertex sum(0.0f);

	for (const auto& vertex : vertices)
	{
		Vertex vertexPosition(vertex.x, vertex.y);
		sum += vertexPosition;// + Vertex(-450, -150);
	}

	Vertex centroid = sum / static_cast<float32>(vertices.size());

	return centroid;
}