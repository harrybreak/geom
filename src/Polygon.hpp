#pragma once

#include "Types.hpp"
#include "Vertex.hpp"
#include "Object.hpp"

#include <vector>
#include <SDL2/SDL.h>
#include "glm/fwd.hpp"
#include <glm/glm.hpp>

class Polygon : public Object
{
private:
	std::vector<Vertex<float32>> m_Vertices;
	SDL_Color m_Color;

public:

	Polygon(const std::vector<Vertex<float32>>& vertices, SDL_Color color);

	const std::vector<Vertex<float32>>& GetVertices() const;

	void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);

	void Rotate(float angle) override;

};