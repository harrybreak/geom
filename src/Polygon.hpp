#pragma once

#include "SDL_pixels.h"
#include "Types.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Object.hpp"

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "glm/fwd.hpp"
#include <glm/glm.hpp>

#include <initializer_list>

/**
 * A Polygon is an object with vertices (m_Vertices) that are connected together making a shape
 * and which coordinates are relative to its Object.position (the inherited class).
 * 
 * It also stores its displaying color (m_Color).
*/
class Polygon : public Object
{
private:
	std::vector<Vertex> m_Vertices;
	std::vector<Edge> m_Edges;

	SDL_Color m_CurrentColor;

public:

	SDL_Color Color;

	Polygon(std::initializer_list<Vertex> vertices, SDL_Color color);
	Polygon(const std::vector<Vertex>& vertices, SDL_Color color);

	// Returns the absolute coordinates of each vertex
	inline constexpr const std::vector<Vertex>& GetVertices() const
	{
		return m_Vertices;
	}

	// Returns the absolute coordinates of each pair of vertices
	inline constexpr const std::vector<Edge>& GetEdges() const
	{
		return m_Edges;
	}

	void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);

	void Rotate(float angle) override;

	void Translate(glm::vec2 delta) override;

	void SetColor(SDL_Color color);

	glm::vec2 ComputeLocalToWorldPosition(glm::vec2 localPosition) const;

	virtual bool Hit(Polygon p);
};