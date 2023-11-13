#pragma once

#include <vector>

#include "Object.hpp"
#include "SDL_render.h"
#include "Types.hpp"
#include <glm/glm.hpp>

class Scene
{

private:

	std::vector<Object*> m_Objects;

public:

	Scene();

	void Instantiate(Object* object);

	Object* GetObject(size_t index);

	void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);

};