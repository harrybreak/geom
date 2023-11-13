#pragma once

#include "Types.hpp"

template<typename T>
struct Vector2
{
	union
	{
		struct
		{
			T x, y;
		};
		struct
		{
			T width, height;
		};
	};

	Vector2() : x(0), y(0)
	{

	}

	Vector2(T x, T y) : x(x), y(y)
	{

	}
};


typedef Vector2<int32> Vector2i;
typedef Vector2<float32> Vector2f;