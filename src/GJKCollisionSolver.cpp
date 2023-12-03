#include "GJKCollisionSolver.hpp"
#include "Polygon.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <limits>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>

Vertex FindFurthestPoint(const Polygon* p, glm::vec2 direction)
{
	std::pair<Vertex, float32> result(glm::vec2(), std::numeric_limits<float32>().lowest());

	for (auto vertex : p->GetVertices())
	{
		float32 dotProduct = glm::dot(vertex, direction);

		//std::cout << "dot: " << "(" << vertex.x << "; " << vertex.y << ")" << " -> " << dotProduct << std::endl;

		if (dotProduct > result.second)
		{
			//std::cout << "dot: " << "(" << vertex.x << "; " << vertex.y << ")" << " -> " << dotProduct << std::endl;

			result.second = dotProduct;
			result.first = vertex;
		}
	}

	return p->ComputeLocalToWorldPosition(result.first);
}

Vertex Support(const Polygon* p, const Polygon* q, glm::vec2 direction)
{
	return FindFurthestPoint(p, direction) - FindFurthestPoint(q, -direction);
}

bool IsOriginInsideLine(std::vector<Vertex>& simplex, glm::vec2& direction)
{
	auto b = simplex[0];
	auto a = simplex[1];

	auto ab = b - a;
	auto ao = glm::vec2(0.f, 0.f) - a;

	auto ab_perpendicular = glm::vec2(glm::cross(glm::cross(glm::vec3(ab, 0), glm::vec3(ao, 0)), glm::vec3(ab, 0)));
	
	direction = ab_perpendicular;
	
	return false;
}

bool IsOriginInsideTriangle(std::vector<Vertex>& simplex, glm::vec2& direction)
{
    auto c = simplex[0];
    auto b = simplex[1];
    auto a = simplex[2];

    auto ab = b - a;
    auto ac = c - a;
    auto ao = glm::vec2(0.f, 0.f) - a;

	auto abPerpendicular = glm::vec2(glm::cross(glm::cross(glm::vec3(ac, 0.f), glm::vec3(ab, 0.f)), glm::vec3(ab, 0.f)));
	auto acPerpendicular = glm::vec2(glm::cross(glm::cross(glm::vec3(ab, 0.f), glm::vec3(ac, 0.f)), glm::vec3(ac, 0.f)));

    if (glm::dot(abPerpendicular, ao) > 0)
    {
        auto it = std::find(simplex.begin(), simplex.end(), c);
        if (it != simplex.end())
        {
            simplex.erase(it);
        }

        direction = abPerpendicular;
        return false;
    }
    else if (glm::dot(acPerpendicular, ao) > 0)
    {
        auto it = std::find(simplex.begin(), simplex.end(), b);
        if (it != simplex.end())
        {
            simplex.erase(it);
        }

        direction = acPerpendicular;
        return false;
    }

    return true;
}


bool IsOriginInsideSimplex(std::vector<Vertex>& simplex, glm::vec2 direction)
{
	if (simplex.size() == 2)
		return IsOriginInsideLine(simplex, direction);

	return IsOriginInsideTriangle(simplex, direction);
}

bool SolveGJK(const Polygon* p, const Polygon* q)
{
	glm::vec2 direction = glm::normalize(q->position - p->position);

	std::vector<Vertex> simplex;
	simplex.push_back(Support(p, q, direction));

	direction = glm::vec2(0.0f, 0.0f) - simplex[0];

	while (true)
	{
		Vertex vtx = Support(p, q, direction);

		if (glm::dot(vtx, direction) < 0)
			return false;
	
		simplex.push_back(vtx);

		if (IsOriginInsideSimplex(simplex, direction))
			return true;
	}

	return false;
}


bool GJKCollisionSolver::IsColliding(const Polygon* p, const Polygon* q)
{
	return SolveGJK(p, q);
}

