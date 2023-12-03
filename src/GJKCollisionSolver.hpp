#pragma once

#include "CollisionSolver.hpp"
class GJKCollisionSolver final : public CollisionSolver
{
public:

	bool IsColliding(const Polygon* p, const Polygon* q) override;
};