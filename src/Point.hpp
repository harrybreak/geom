
#pragma once

#include "Object.hpp"
#include "Types.hpp"
#include "SDL_pixels.h"

/**
 * Default width of points (in pixel)
 * Points are represented as small squares on the screen
 */
#define DOT_SIZE 5

/**
 * General point object structure
 * 
 * A point is drawn as a small square
 * centered on Object.position in the world.
 * A point has a drawing color
 */
struct Point : public Object
{
	/* Color of the point */
	SDL_Color color;

	Point();
	Point(float32, float32, SDL_Color);
	Point(glm::vec2, SDL_Color);

	/* Render method overrided from the Object class */
	void Render(SDL_Renderer*, glm::mat3) override;
};
