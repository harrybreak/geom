#include "Application.hpp" 
#include "PhysicsEngine.hpp"
#include "Scene.hpp"
#include "glm/fwd.hpp"
#include <string>
#include <limits>


Application::Application(Scene* scene) : 
m_Window(nullptr), m_Renderer(nullptr), m_WindowExtent(), m_pScene(scene), m_ViewportScale(4, 4), m_ViewportTransform(1), physicsEngine(m_pScene)
{

}

void Application::Init()
{
    SDL_Init(SDL_INIT_VIDEO);

    m_Window = SDL_CreateWindow("Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (m_Window == nullptr || m_Renderer == nullptr)
        return;

	physicsEngine.Init(PhysicsEngine::CollisionSolverType::SAT);
}


void Application::Shutdown()
{
	physicsEngine.Shutdown();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Application::RenderScene(SDL_Renderer* renderer, Vertex viewportOffset)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	DrawGrid(renderer, viewportOffset);
}


void Application::DrawGrid(SDL_Renderer* renderer, Vertex viewportOffset)
{
	const int32 unitSize = 20;

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	for (int32 i = -unitSize; i < m_WindowExtent.x + unitSize; i += unitSize)
	{
		SDL_RenderDrawLine(renderer, i + (int)viewportOffset.x % unitSize, (int)viewportOffset.y % unitSize, i + (int)viewportOffset.x % unitSize, (int)m_WindowExtent.y);
	}
	for (int32 i = -unitSize; i < m_WindowExtent.y + unitSize; i += unitSize)
	{
		SDL_RenderDrawLine(renderer, (int)viewportOffset.x % unitSize, i + (int)viewportOffset.y % unitSize, (int)m_WindowExtent.x, i + (int)viewportOffset.y % unitSize);
	}

}


void Application::DrawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void Application::Run()
{
	m_ViewportTransform = glm::scale(glm::mat4(m_ViewportTransform), glm::vec3(m_ViewportScale, 1));
	Init();


    bool isRunning = true;
    SDL_Event event;

    bool isDragging = false;

	Vertex lastMousePosition;

	m_WindowExtent.x = DEFAULT_WINDOW_WIDTH;
	m_WindowExtent.y = DEFAULT_WINDOW_HEIGHT;

	uint32 index = 0;

    while (isRunning)
    {
		physicsEngine.Update();

		m_pScene->at(1)->Rotate(0.01f);

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
						m_pScene->at(index)->Translate(glm::vec2(-1.0f, 0.0f));
                        break;
                    case SDLK_RIGHT:
						m_pScene->at(index)->Translate(glm::vec2(1.0f, 0.0f));
                        break;
                    case SDLK_UP:
						m_pScene->at(index)->Translate(glm::vec2(0.0f, -1.0f));
                        break;
                    case SDLK_DOWN:
						m_pScene->at(index)->Translate(glm::vec2(0.0f, 1.0f));
                        break;
                    case SDLK_p:
						m_pScene->at(index)->Rotate(5.0f);
						break;
					case SDLK_n:
						index = ++index % m_pScene->size();
						break;
                }
            }

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_WindowExtent.x = event.window.data1;
                m_WindowExtent.y = event.window.data2;
            }

            if (event.type == SDL_MOUSEWHEEL)
            {
                if (event.wheel.y != 0)
                {
                    if (SDL_GetModState() & KMOD_SHIFT)
                    {
						m_ViewportTransform[2][0] -= event.wheel.y * 10;
                    }
                    else
                    {
						m_ViewportTransform[2][1] -= event.wheel.y * 10;
                    }
                }
            }


            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = true;
				lastMousePosition.x = event.button.x;
				lastMousePosition.y = event.button.y;
            }

            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = false;
            }

            if (isDragging && event.type == SDL_MOUSEMOTION)
            {
				Vertex mouseDelta(event.motion.x - lastMousePosition.x, event.motion.y - lastMousePosition.y);

				m_ViewportTransform[2][0] += mouseDelta.x;
				lastMousePosition.x = event.motion.x;

				m_ViewportTransform[2][1] += mouseDelta.y;
				lastMousePosition.y = event.motion.y;
            }
        }

		RenderScene(m_Renderer, Vertex(m_ViewportTransform[2][0], m_ViewportTransform[2][1]));
		m_pScene->Render(m_Renderer, m_ViewportTransform);

        SDL_RenderPresent(m_Renderer);
    }

	Shutdown();
}
