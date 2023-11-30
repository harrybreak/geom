#include <algorithm>
#include <limits>

#include "SATCollisionSolver.hpp"
#include "Polygon.hpp"
#include "Types.hpp"
#include "Vertex.hpp"
#include "glm/fwd.hpp"

#include <iostream>

float32 SATCollisionSolver::FindMinimumSeparationDistance(const Polygon* p, const Polygon* q)
{
    float32 separationDistance = std::numeric_limits<float>::lowest();

	for (auto pEdge : p->GetEdges())
    {
		float32 minSeparationDistance = std::numeric_limits<float32>::max();

        for (auto qVertex : q->GetVertices())
        {
			// Project the vertices on the normal (perpendicualr to the edge) axis.
            float32 projection = glm::dot(q->ComputeLocalToWorldPosition(qVertex) - p->ComputeLocalToWorldPosition(pEdge.GetSource()), pEdge.ComputeNormal());
			minSeparationDistance = std::min(minSeparationDistance, projection);
        }

        separationDistance = std::max(separationDistance, minSeparationDistance);
    }

    return separationDistance;
}


bool SATCollisionSolver::IsColliding(const Polygon* p, const Polygon* q)
{
    return FindMinimumSeparationDistance(p, q) <= 0 && FindMinimumSeparationDistance(q, p) <= 0;
}