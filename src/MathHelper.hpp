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

void RRotate(glm::vec2* vertexCoordinates, glm::vec2 pivot, float angle);
//Deprecated
glm::vec2 ComputeCentroid(const std::vector<Vertex>& vertices);

float ComputeOrientation(const glm::vec3& verticeA, const glm::vec3& verticeB, const glm::vec3& verticeC);

int InclusionTest(Polygon* polygon, const glm::vec2& testVertex);