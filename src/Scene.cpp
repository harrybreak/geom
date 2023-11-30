#include "Scene.hpp"
#include "Object.hpp"


Scene::Scene() : m_Objects()
{

}

const std::vector<Object*>& Scene::GetObjects() const
{
	return m_Objects;
}


void Scene::Instantiate(Object* object)
{
    m_Objects.push_back(object);
}

Object* Scene::GetObject(size_t index)
{
	return m_Objects[index];
}

void Scene::Render(SDL_Renderer* renderer, glm::mat3 projectionTransform)
{
	for (auto& object : m_Objects)
		object->Render(renderer, projectionTransform);
}
