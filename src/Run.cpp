#include <vector>

#include "MathHelper.hpp"
#include "Types.hpp"
#include "Application.hpp"
#include "Vertex.hpp"
#include "Polygon.hpp"
#include "Scene.hpp"
#include "Point.hpp"
#include "glm/fwd.hpp"

#include <iostream>

Vertex FFindFurthestPoint(const Polygon* p, glm::vec2 direction)
{
	std::pair<Vertex, float32> result(glm::vec2(), std::numeric_limits<float32>().lowest());

	for (auto vertex : p->GetVertices())
	{
		float32 dotProduct = glm::dot(vertex, direction);

		//std::cout << "dot: " << "(" << vertex.x << "; " << vertex.y << ")" << " -> " << dotProduct << std::endl;

		if (dotProduct > result.second)
		{
			std::cout << "dot: " << "(" << vertex.x << "; " << vertex.y << ")" << " -> " << dotProduct << std::endl;

			result.second = dotProduct;
			result.first = vertex;
		}
	}

	return result.first;
}

int32 main()
{

	std::cout << "TEST: " << ComputeOrientation(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(20.0f, 10.0f, 0.0f), glm::vec3(0.0f, 60.0f, 0.0f)) << std::endl;




	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(10,10));
	vertices.push_back(Vertex(10,-10));
	vertices.push_back(Vertex(-10,-10));
	vertices.push_back(Vertex(-10,10));

	SDL_Color polygonColor = {0, 255, 0, 255};

	Polygon polygon(vertices, polygonColor);

	/*Vertex v = FFindFurthestPoint(&polygon, glm::vec2(1, 1));

	std::cout << "(" << v.x << "; " << v.y << ")" << std::endl;

	return 0;*/

	//polygon.Translate(glm::vec2(-500, -200));
	//polygon.Rotate(180.0f);

	std::vector<Vertex> vertices2;
	//vertices2.push_back(Vertex(10, 12));
	//vertices2.push_back(Vertex(2, 50));
	//vertices2.push_back(Vertex(32, 25));
	//vertices2.push_back(Vertex(65, 10));
	vertices2.push_back(Vertex(10,10));
	vertices2.push_back(Vertex(10,-10));
	vertices2.push_back(Vertex(-10,-10));
	vertices2.push_back(Vertex(-10,10));

	SDL_Color polygonColor2 = {0, 0, 255, 255};

	Polygon polygon2(vertices2, polygonColor2);
	polygon2.Translate(glm::vec2(-20, 20));



	std::vector<Vertex> vertices3;
	vertices3.push_back(Vertex(10,10));
	vertices3.push_back(Vertex(10,-10));
	vertices3.push_back(Vertex(-10,-10));
	vertices3.push_back(Vertex(-10,10));
	//vertices3.push_back(Vertex(80, -80));
	SDL_Color polygonColor4 = {120, 80, 200, 255};
	Polygon polygon3(vertices3, polygonColor4);
	polygon3.Translate(glm::vec2(-20, 60));

	SDL_Color polygonColor3 = {0, 255, 0, 255};
	Point p1(100, 100, polygonColor3);
	p1.Translate(glm::vec2(-500, -200));

	Scene scene;
	scene.Instantiate(&polygon);
	scene.Instantiate(&polygon2);
	scene.Instantiate(&polygon3);
	//scene.Instantiate(&p1);

	
	Application application(&scene);
	application.Run();

	//if (polygon.Hit(polygon2))
	//	std::cout << "The red square hits the blue weird shape" << std::endl;

	return 0;
}