#include <vector>

#include "Types.hpp"
#include "Application.hpp"
#include "Vertex.hpp"
#include "Polygon.hpp"
#include "Scene.hpp"
#include "Point.hpp"
#include "glm/fwd.hpp"

int32 main()
{
	std::vector<Vertex<float32>> vertices;
	vertices.push_back(Vertex<float32>(10,10));
	vertices.push_back(Vertex<float32>(10,-10));
	vertices.push_back(Vertex<float32>(-10,-10));
	vertices.push_back(Vertex<float32>(-10,10));

	SDL_Color polygonColor = {255, 0, 0, 255};

	Polygon polygon(vertices, polygonColor);
	//polygon.Translate(glm::vec2(-500, -200));
	//polygon.Rotate(180.0f);

	std::vector<Vertex<float32>> vertices2;
	vertices2.push_back(Vertex<float32>(10, 12));
	vertices2.push_back(Vertex<float32>(2, 50));
	vertices2.push_back(Vertex<float32>(32, 25));
	vertices2.push_back(Vertex<float32>(65, 10));

	SDL_Color polygonColor2 = {0, 0, 255, 255};

	Polygon polygon2(vertices2, polygonColor2);
	polygon2.Translate(glm::vec2(-200, 150));

	SDL_Color polygonColor3 = {0, 255, 0, 255};
	Point p1(100, 100, polygonColor3);
	p1.Translate(glm::vec2(-500, -200));

	Scene scene;
	scene.Instantiate(&polygon);
	scene.Instantiate(&polygon2);
	scene.Instantiate(&p1);

	Application application(&scene);
	application.Run();

	if (polygon.Hit(polygon2))
		std::cout << "The red square hits the blue weird shape" << std::endl;

	return 0;
}