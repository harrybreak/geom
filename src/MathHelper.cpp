#include "MathHelper.hpp"
#include <iostream>

void RRotate(glm::vec2* vertexCoordinates, glm::vec2 pivot, float angle)
{
	glm::mat4 translateToPivot = glm::translate(glm::mat4(1), glm::vec3(pivot, 1));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), glm::vec3(-pivot, 1));
	glm::mat4 finalTransformation = translateBack * rotationMatrix * translateToPivot;
	glm::vec4 transformedPosition = finalTransformation * glm::vec4(glm::vec3(*vertexCoordinates, 1.0f), 1.0f);
	*vertexCoordinates = glm::vec2(transformedPosition);
}

//Deprecated
glm::vec2 ComputeCentroid(const std::vector<Vertex>& vertices)
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

float ComputeOrientation(const glm::vec3& verticeA, const glm::vec3& verticeB, const glm::vec3& verticeC)
{
    glm::vec3 u = verticeB - verticeA;
    glm::vec3 v = verticeC - verticeB;
    glm::vec3 result = glm::cross(u, v);
    return result.z;
}


int InclusionTest(Polygon* polygon, const glm::vec2& testVertex)
{
    int counterLeft = 0;
    int counterRight = 0;
    bool overlap = false;

    for (size_t i = 0; i < polygon->GetVertices().size() - 1; i++)
	{
		//std::cout << "1 (" << polygon->GetVertices()[i % 3].x << "; " << polygon->GetVertices()[i % 3].y << ")" << std::endl;
		//std::cout << "2 (" << polygon->GetVertices()[(i + 1) % 3].x << "; " << polygon->GetVertices()[(i + 1) % 3].y << ")" << std::endl;
		//std::cout << "3 (" << testVertex.x << "; " << testVertex.y << ")" << std::endl;


        float orientation = ComputeOrientation(glm::vec3(polygon->ComputeLocalToWorldPosition(polygon->GetVertices()[i % 3]), 1), 
											   glm::vec3(polygon->ComputeLocalToWorldPosition(polygon->GetVertices()[(i + 1) % 3]), 1), 
											   glm::vec3(testVertex, 1));

        if (orientation > 0)
			counterLeft++;
        else if (orientation < 0)
			counterRight++;
        else
			overlap = true;

    }

    if (overlap)
		return 0;
    else if (counterLeft == 3 || counterRight == 3)
	{
		std::cout << "Inside" << std::endl;
		return 1;
	}
    else
	{
		std::cout << "Outside" << std::endl;
		return -1;
	}
}