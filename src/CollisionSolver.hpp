#pragma once

#include "Std.hpp"

#include "Polygon.hpp"

class CollisionSolver
{
public:

	virtual bool IsColliding(const Polygon* p, const Polygon* q) pure;
};