#pragma once

#include "CollisionSolver.hpp"
#include "Polygon.hpp"

/**
 * The SAT Collision Solver's class
 * 
 * It provides an intermediate method to find
 * the minimum separation distance between 2 polygons.
 */
class SATCollisionSolver final : public CollisionSolver
{
public:

	SATCollisionSolver() = default;

	/**
	 * Returns the minimum separation distance between two distinct given polygon.
	 * When both polygons hit each others, it returns minus infinity.
	*/
	float FindMinimumSeparationDistance(const Polygon* p, const Polygon* q);

	/* Overrided collision test using SAT method */
	bool IsColliding(const Polygon* p, const Polygon* q) override;
};