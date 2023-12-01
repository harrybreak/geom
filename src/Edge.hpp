#pragma once

#include "Vertex.hpp"

#include <glm/glm.hpp>

/**
 * Edge general structure
 * 
 * Edge is a structure defined by two distinct vertices : a source and a destination
 * Despite the fact that polygon's edges do not need to have directions, it has been
 * decided to keep this general definition in case of need.
*/
struct Edge
{
private:
	Vertex* m_pSource, *m_pDestination;

public:

	Edge(Vertex* source, Vertex* destination) : m_pSource(source), m_pDestination(destination) {}

	/* Returns a constexpr reference to the edge's source vertex */
	inline constexpr Vertex& GetSource() const { return *m_pSource; }

	/* Returns a constexpr reference to the edge's destination vertex */
	inline constexpr Vertex& GetDestination() const	{ return *m_pDestination; }

	/* Returns a copy of the left directed normal vector of the edge */
	inline glm::vec2 ComputeNormal() const
	{
		glm::vec2 direction = *(m_pDestination) - *(m_pSource);

		return glm::normalize(glm::vec2(-direction.y, direction.x));
	}
};