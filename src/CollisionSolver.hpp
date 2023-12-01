#pragma once

#include "Std.hpp"
#include "Polygon.hpp"

/**
 * Abstract Collision Solver class
 * 
 * It is derived by SATCollisionSolver and GJKCollisionSolver
 */
class CollisionSolver
{
	public:
		virtual bool IsColliding(const Polygon* p, const Polygon* q) pure;
};
