#include "Polygon.hpp"
#include "Types.hpp"
#include "Viewport.hpp"
#include "MathHelper.hpp"
#include "glm/fwd.hpp"

#include <iostream>

Polygon::Polygon(const std::vector<Vertex<float32>>& vertices, SDL_Color color) : m_Vertices(vertices), m_Color(color)
{

}

const std::vector<Vertex<float32>>& Polygon::GetVertices() const
{
	return m_Vertices;
}


void Polygon::Render(SDL_Renderer* renderer, glm::mat3 projectionTransform)
{
    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);

    Vertex<float32> firstVertex = m_Vertices.back();

    for (const Vertex<float32>& vertex : m_Vertices)
    {
		//glm::vec3 screenSpaceCoordinates = projectionTransform * glm::vec3(vertex.x, vertex.y, 1);

		glm::vec2 v1(position.x + firstVertex.x, position.y + firstVertex.y);
		glm::vec2 v2(position.x + vertex.x, position.y + vertex.y);

		auto screenSpaceCoordinatesV1 = Viewport::TransformToScreenSpace(v1, projectionTransform);
		auto screenSpaceCoordinatesV2 = Viewport::TransformToScreenSpace(v2, projectionTransform);

        SDL_RenderDrawLine(renderer, screenSpaceCoordinatesV1.x, screenSpaceCoordinatesV1.y, screenSpaceCoordinatesV2.x, screenSpaceCoordinatesV2.y);
        firstVertex = vertex;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Polygon::Rotate(float angle)
{

	for (auto& vertex : m_Vertices)
	{
		glm::vec2 vertexPosition(vertex.x, vertex.y);

		RRotate(&vertexPosition, position, angle);
		//RRotate(&vertexPosition, ComputeCentroid(m_Vertices), angle);
		vertex.x = vertexPosition.x;
		vertex.y = vertexPosition.y;
	}
}
