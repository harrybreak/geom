#include "Object.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

Object::Object() : position(0, 0)
{

}

Object::Object(glm::vec2 position) : position(position)
{

}

void Object::Translate(glm::vec2 delta)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::vec3(delta, 0));
	glm::vec4 translatedPosition = translationMatrix * glm::vec4(position, 1, 1);

	position = glm::vec2(translatedPosition);
}

void Object::Scale(glm::vec2 factor)
{

}

void Object::Rotate(glm::vec2 pivot, float32 angle)
{

}

void Object::Rotate(float angle)
{

}