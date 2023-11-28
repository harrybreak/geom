#pragma once

#include "Types.hpp"
#include "Vertex.hpp"
#include "Object.hpp"

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "glm/fwd.hpp"
#include <glm/glm.hpp>

/**
 * A Polygon is an object with vertices (m_Vertices) that are connected together making a shape
 * and which coordinates are relative to its __position__.
 * 
 * It also stores its displaying color (m_Color)
*/
class Polygon : public Object
{
private:
	std::vector<Vertex<float32>> m_Vertices;
	SDL_Color m_Color;

public:

	Polygon(const std::vector<Vertex<float32>>& vertices, SDL_Color color);

	// Returns the absolute coordinates of each vertex
	std::vector<Vertex<float32>> GetVertices();

	// Returns the absolute coordinates of each pair of vertices
	std::vector<segment> GetEdges();

	void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);

	void Rotate(float angle) override;

	void Translate(glm::vec2 delta) override;

	virtual bool Hit(Polygon p);
};