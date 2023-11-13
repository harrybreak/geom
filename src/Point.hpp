
#pragma once

#include "Object.hpp"
#include "Types.hpp"
#include "SDL_pixels.h"


#define DOT_SIZE 5

struct Point : public Object
{
	//float32 x, y;
	SDL_Color color;

	Point();

	Point(float32 x, float32 y, SDL_Color color);

	void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform);
};