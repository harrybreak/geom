#pragma once

#include "Vertex.hpp"

#include <glm/glm.hpp>

struct Edge
{
private:
	Vertex* m_pSource, *m_pDestination;

public:

	Edge(Vertex* source, Vertex* destination) : m_pSource(source), m_pDestination(destination)
	{

	}

	inline constexpr Vertex& GetSource() const
	{
		return *m_pSource;
	}

	inline constexpr Vertex& GetDestination() const
	{
		return *m_pDestination;
	}

	inline glm::vec2 ComputeNormal() const
	{
		glm::vec2 direction = *(m_pDestination) - *(m_pSource);

		return glm::normalize(glm::vec2(-direction.y, direction.x));
	}
};