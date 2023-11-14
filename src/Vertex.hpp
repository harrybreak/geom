#pragma once

#include "Types.hpp"
#include "Vector2.hpp"
#include <glm/glm.hpp>

template<typename T>
struct Vertex
{
	T x, y;

	Vertex(T x, T y);
	Vertex(const glm::vec2& v) : x(v.x), y(v.y) {}
	Vertex<T> operator+=(const Vertex<T>& a) { return Vertex<T>(x + a.x,y + a.y); }
	Vertex<T> operator-=(const Vertex<T>& a) { return Vertex<T>(x - a.x,y - a.y); }
	Vertex<T> operator/=(const float32 d)	 { return Vertex<T>(x/d, y/d); }
	Vertex<T> operator*=(const float32 d)	 { return Vertex<T>(x*d, y*d); }
};

template<typename T>
Vertex<T> operator-(Vertex<T> a, Vertex<T> b) { return Vertex<T>(a.x - b.x , a.y - b.y); }
template<typename T>
Vertex<T> operator+(Vertex<T> a, Vertex<T> b) { return Vertex<T>(a.x + b.x , a.y + b.y); }

typedef std::pair<Vertex<float32>,Vertex<float32>> segment;


#include "Vertex.inl"