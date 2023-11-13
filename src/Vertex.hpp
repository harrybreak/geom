#pragma once

#include "Types.hpp"
#include "Vector2.hpp"

template<typename T>
struct Vertex
{
	T x, y;

	Vertex(T x, T y);
};

#include "Vertex.inl"