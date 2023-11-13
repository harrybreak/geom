#include "Point.hpp"
#include "Object.hpp"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "Viewport.hpp"
#include "glm/fwd.hpp"


Point::Point() : Object(glm::vec2(0, 0))
{

}

Point::Point(float32 x, float32 y, SDL_Color color) : Object(glm::vec2(x, y)), color(color)
{

}

void Point::Render(SDL_Renderer* renderer, glm::mat3 projectionTransform)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	auto screenSpaceCoordinate = Viewport::TransformToScreenSpace(position, projectionTransform);
	//SDL_RenderDrawPoint(renderer, screenSpaceCoordinate.x, screenSpaceCoordinate.y);
	SDL_Rect point = {static_cast<int32>(screenSpaceCoordinate.x), static_cast<int32>(screenSpaceCoordinate.y), DOT_SIZE, DOT_SIZE};
	SDL_RenderFillRect(renderer, &point);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}