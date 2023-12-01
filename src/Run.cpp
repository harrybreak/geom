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
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(10,10));
	vertices.push_back(Vertex(10,-10));
	vertices.push_back(Vertex(-10,-10));
	vertices.push_back(Vertex(-10,10));

	SDL_Color polygonColor = {0, 255, 0, 255};

	Polygon polygon(vertices, polygonColor);
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
	scene.push_back(&polygon);
	scene.push_back(&polygon2);
	scene.push_back(&polygon3);

	
	Application application(&scene);
	application.Run();

	//if (polygon.Hit(polygon2))
	//	std::cout << "The red square hits the blue weird shape" << std::endl;

	return 0;
}