#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "Scene.hpp"
#include "Types.hpp"

#include <SDL2/SDL.h>
//#include <SDL_ttf.h>

#include "Vector2.hpp"
#include <glm/glm.hpp>
#include "glm/fwd.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "PhysicsEngine.hpp"


#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

#define SCALE 20



class Application
{
private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

	Scene* m_pScene;

	PhysicsEngine physicsEngine;

	glm::vec2 m_ViewportScale;
	glm::mat3 m_ViewportTransform;

	//Vector2i m_ViewportOffset;
	Vector2i m_WindowExtent;

	//Text
	std::vector<SDL_Surface*> m_TextSurfaces;
	std::vector<SDL_Texture*> m_TextTextures;

public:

	Application(Scene* scene);

	void Init();

	void Run();

private:

	void Shutdown();

	void DrawGrid(SDL_Renderer* renderer, Vector2i viewportOffset);

	void RenderScene(SDL_Renderer* renderer, Vector2i viewportOffset);

	void DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color);

};