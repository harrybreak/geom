#include "Polygon.hpp"
#include "Types.hpp"
#include "Viewport.hpp"
#include "MathHelper.hpp"
#include "glm/fwd.hpp"

#include <iostream>

Polygon::Polygon(const std::vector<Vertex<float32>>& vertices, SDL_Color color) : m_Color(color)
{
	m_Vertices.clear();
	Vertex<float32> bar((float32) 0.0, (float32)0.0);
	for (const Vertex<float32>& vert : vertices) bar += vert;
	bar /= ((float32)vertices.size());
	position.x = bar.x;
	position.y = bar.y;
	for (Vertex<float32> vert : vertices) m_Vertices.push_back(vert - bar);
}

std::vector<Vertex<float32>> Polygon::GetVertices()
{
	std::vector<Vertex<float32>> r = std::vector<Vertex<float32>>();
	for (auto vert : m_Vertices)
		r.push_back(vert + Vertex<float32>(position));
	return r;
}

std::vector<segment> Polygon::GetEdges()
{
	std::vector<segment> r = std::vector<segment>();
	Vertex<float32> firstVertex = m_Vertices.back() + Vertex<float32>(position);
	for (auto vert : m_Vertices)
	{
		r.push_back({firstVertex + Vertex<float32>(position) , vert + Vertex<float32>(position)});
		firstVertex = vert;
	}
	return r;
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
		RRotate(&vertexPosition, glm::vec2(0, 0), angle);
		vertex.x = vertexPosition.x;
		vertex.y = vertexPosition.y;
	}
}

void Polygon::Translate(glm::vec2 delta)
{
	Object::Translate(delta);

	for (auto& vertex : m_Vertices)
		std::cout << "Vertex: (" << (vertex.x + position.x) << "; " << (vertex.y + position.y) << ")" << std::endl;
}


bool Polygon::Hit(Polygon p)
{
	std::vector<segment> myEdges = GetEdges();
	std::vector<segment> itsEdges= p.GetEdges();

	for (auto myEdge : myEdges)
	{
		for (auto itsEdge : itsEdges)
		{
			if (det(myEdge.first, itsEdge.first, itsEdge.second)* det(myEdge.second, itsEdge.first, itsEdge.second)<= 0 &&
				det(itsEdge.first, myEdge.first, myEdge.second) * det(itsEdge.second, myEdge.first, myEdge.second) <= 0)
				return true;
		}
	}

	return false;
}
