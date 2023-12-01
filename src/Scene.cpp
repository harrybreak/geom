#include "Scene.hpp"
#include "Object.hpp"

void Scene::Render(SDL_Renderer* renderer, glm::mat3 projectionTransform)
{
	for (std::size_t k = 0 ; k < size() ; k++)
		at(k)->Render(renderer, projectionTransform);
}
