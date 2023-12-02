#include "Polygon.hpp"
#include "Types.hpp"
#include "Viewport.hpp"
#include "MathHelper.hpp"
#include "glm/fwd.hpp"

#include <cstddef>
#include <iostream>

Polygon::Polygon(const std::vector<Vertex>& vertices, SDL_Color color) : Color(color), m_CurrentColor(color), m_Vertices()
{
	// Vertex position must be stored relative to the polygon position aka polygon centroid.
	// In other world vertex position are local to the polygon.

	for (auto worldVertex : vertices) //TODO: add WorldToLocal and LocalToWorld
		m_Vertices.push_back(Vertex(worldVertex.x + position.x, worldVertex.y + position.y));

	for (size_t i = 0; i < vertices.size(); i++)
		m_Edges.emplace_back(Edge(&m_Vertices[i % vertices.size()], &m_Vertices[(i + 1) % vertices.size()]));

	std::cout << "Vertex count: " << m_Vertices.size() << std::endl;
	std::cout << "Edge count: " << m_Edges.size() << std::endl;

	for (auto edge : m_Edges)
		std::cout << "{" << "(" << edge.GetSource().x << "; " << edge.GetSource().y << ")" << ", " << "(" << edge.GetDestination().x << "; " << edge.GetDestination().y << ")" << "}" << std::endl;

}


void Polygon::Render(SDL_Renderer* renderer, glm::mat3 projectionTransform)
{
    SDL_SetRenderDrawColor(renderer, m_CurrentColor.r, m_CurrentColor.g, m_CurrentColor.b, m_CurrentColor.a);

    Vertex firstVertex = m_Vertices.back();

    for (const Vertex& vertex : m_Vertices)
    {
		//glm::vec3 screenSpaceCoordinates = projectionTransform * glm::vec3(vertex.x, vertex.y, 1);

		glm::vec2 v1(position.x + firstVertex.x, position.y + firstVertex.y);
		glm::vec2 v2(position.x + vertex.x, position.y + vertex.y);

		auto screenSpaceCoordinatesV1 = Viewport::TransformWorldToScreenSpace(v1, projectionTransform);
		auto screenSpaceCoordinatesV2 = Viewport::TransformWorldToScreenSpace(v2, projectionTransform);

        SDL_RenderDrawLine(renderer, screenSpaceCoordinatesV1.x, screenSpaceCoordinatesV1.y, screenSpaceCoordinatesV2.x, screenSpaceCoordinatesV2.y);
        firstVertex = vertex;
    }

	for (auto edge : m_Edges)
	{
		// Calculate the midpoint of the edge
		glm::vec2 midpoint = 0.5f * ((edge.GetSource()) + (edge.GetDestination()));

		// Transform the midpoint to screen space coordinates
		glm::vec2 v(midpoint.x + position.x, midpoint.y + position.y);
		auto screenSpaceCoordinatesV = Viewport::TransformWorldToScreenSpace(v, projectionTransform);

		// DEBUG: Draw the normals
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(renderer,
						static_cast<int>(screenSpaceCoordinatesV.x),
						static_cast<int>(screenSpaceCoordinatesV.y),
						static_cast<int>(screenSpaceCoordinatesV.x + edge.ComputeNormal().x * 10.0f),
						static_cast<int>(screenSpaceCoordinatesV.y + edge.ComputeNormal().y * 10.0f));
	}


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Polygon::Rotate(float angle)
{
	for (auto& vertex : m_Vertices)
	{
		glm::vec2 vertexPosition(vertex.x, vertex.y);
		RRotate(&vertexPosition, glm::vec2(0, 0), angle);
		vertex.x = vertexPosition.x;
		vertex.y = vertexPosition.y;
	}
}

void Polygon::Translate(glm::vec2 delta)
{
	Object::Translate(delta);

	std::cout << "--------------------------" << std::endl;

	for (auto& vertex : m_Vertices)
	{
		std::cout << "Vertex: (" << (vertex.x + position.x) << "; " << (vertex.y + position.y) << ")" << std::endl;
	}
}


void Polygon::SetColor(SDL_Color color)
{
	m_CurrentColor = color;
}


glm::vec2 Polygon::ComputeLocalToWorldPosition(glm::vec2 localPosition) const
{
	return localPosition + position;
}



bool Polygon::Hit(Polygon p)
{
	/*std::vector<Edge> myEdges = GetEdges();
	std::vector<Edge> itsEdges= p.GetEdges();

	for (auto myEdge : myEdges)
	{
		for (auto itsEdge : itsEdges)
		{
			if (det(myEdge.GetSource(), itsEdge.GetSource(), itsEdge.GetDestination())* det(myEdge.GetDestination(), itsEdge.GetSource(), itsEdge.GetDestination())<= 0 &&
				det(itsEdge.GetSource(), myEdge.GetSource(), myEdge.GetDestination()) * det(itsEdge.GetDestination(), myEdge.GetSource(), myEdge.GetDestination()) <= 0)
				return true;
		}
	}

	return false;*/
}
