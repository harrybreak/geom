#pragma once

#include <vector>

#include "Object.hpp"
#include "SDL_render.h"
#include "Types.hpp"
#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include "Polygon.hpp"

class Scene
{

private:

	std::vector<Object*> m_Objects;

public:

	Scene();

	void Instantiate(Object* object);

	Object* GetObject(size_t index);

	const std::vector<Object*>& GetObjects() const;

	Polygon* PickObject(glm::vec2 mousePosition) const;

	void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);

};