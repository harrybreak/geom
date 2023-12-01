#include "Point.hpp"
#include "Object.hpp"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "Viewport.hpp"
#include "glm/fwd.hpp"


Point::Point() : Object(glm::vec2(0, 0)) {}

Point::Point(float32 x, float32 y, SDL_Color color) : Object(glm::vec2(x, y)), color(color) {}

Point::Point(glm::vec2 v, SDL_Color color) : Object(v), color(color) {}

void Point::Render(SDL_Renderer* renderer, glm::mat3 projectionTransform)
{
	// Set the brush of the renderer with the point color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	// Get the origin position of the point in screen coordinate system
	auto screenSpaceCoordinate = Viewport::TransformToScreenSpace(position, projectionTransform);
	// Center the point around its origin point (why is it substracted by half of dot_size)
	SDL_Rect point = {
		static_cast<int32>(screenSpaceCoordinate.x - DOT_SIZE/2.f) /* x position casted from float to int32 */,
		static_cast<int32>(screenSpaceCoordinate.y - DOT_SIZE/2.f) /* y position casted from float to int32 */,
		DOT_SIZE, DOT_SIZE /* (w,h), width and height of the rectangle */};
	SDL_RenderFillRect(renderer, &point);
	// Finally leave the renderer with color RGB(255,255,255,255)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}