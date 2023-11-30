#pragma once

#include "CollisionSolver.hpp"
#include "Polygon.hpp"

class SATCollisionSolver final : public CollisionSolver
{
public:

	SATCollisionSolver() = default;

	float FindMinimumSeparationDistance(const Polygon* p, const Polygon* q);

	bool IsColliding(const Polygon* p, const Polygon* q) override;
};