#pragma once

#include "Types.hpp"
#include "glm/fwd.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Object
{
protected:
	uint32 m_Id;

	glm::vec2 m_Scale;
	float m_Rotation;

public:
	glm::vec2 position;

	Object();

	Object(glm::vec2 position);

	uint32 GetId() const
	{
		return m_Id;
	}

	virtual void Translate(glm::vec2 delta);

	virtual void Scale(glm::vec2 factor);
	
	virtual void Rotate(glm::vec2 pivot, float32 angle);

	virtual void Rotate(float angle);

	virtual void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform) = 0;


};