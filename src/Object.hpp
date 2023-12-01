#pragma once

#include "Types.hpp"
#include "glm/fwd.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

/**
 * General scene object class
 * 
 * Each object is defined by an own 32-bit identifier.
 * Every type of drawable object derives from this class,
 * and each of them needs three global parameters :
 *  - the position vector
 *  - the relative scaling vector (initialized at (1,1))
 *  - the relative rotation angle (initialized at 0.0f) (in degrees, not radians!)
 * 
 * Each drawable object derived from this class can be translated, scaled, rotated and
 * rendered into any given SDL_Renderer* 
*/

class Object
{
protected:
	uint32 m_Id;

	glm::vec2 m_Scale;
	float m_Rotation;

	static uint32 s_count;

public:
	glm::vec2 position;

	Object();
	Object(glm::vec2 position);

	/* Returns a const copy of the object's id */
	uint32 GetId() const {	return m_Id; }

	/* Translate the origin position vector of the object by 'delta' */
	virtual void Translate(glm::vec2 delta);

	/**
	 * Overrided methods /!\
	*/
	virtual void Scale(glm::vec2 factor);
	virtual void Rotate(glm::vec2 pivot, float32 angle);
	virtual void Rotate(float angle);

	/* Render the drawable object. This method is also overrided in children classes
	   but it has a working default algorithm for every object instead of Scale() */
	virtual void Render(SDL_Renderer* renderer, glm::mat3 projectionTransform) = 0;
};
