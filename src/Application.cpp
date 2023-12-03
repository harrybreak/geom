#include "Application.hpp" 
#include "PhysicsEngine.hpp"
#include "Scene.hpp"
#include "Vector2.hpp"
#include "Viewport.hpp"
#include "glm/fwd.hpp"
#include <string>
#include <limits>
#include <chrono>



//TTF_Font* font = nullptr;

Application::Application(Scene* scene) : 
m_Window(nullptr), m_Renderer(nullptr), /*m_ViewportOffset(),*/ m_WindowExtent(), m_pScene(scene), m_ViewportScale(4, 4), m_ViewportTransform(1), physicsEngine(m_pScene)
{

}

void Application::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    //TTF_Init();

    m_Window = SDL_CreateWindow("Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (m_Window == nullptr || m_Renderer == nullptr)
        return;

	physicsEngine.Init(PhysicsEngine::CollisionSolverType::GJK);

    /*font = TTF_OpenFont("JetBrainsMono-Regular.ttf", 20);

    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
        exit(1);
    }*/
}


void Application::Shutdown()
{
	//TTF_CloseFont(font);
    //TTF_Quit();

	physicsEngine.Shutdown();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Application::RenderScene(SDL_Renderer* renderer, Vector2i viewportOffset)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	DrawGrid(renderer, viewportOffset);
}


void Application::DrawGrid(SDL_Renderer* renderer, Vector2i viewportOffset)
{
	const int32 unitSize = 20;

	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	for (int32 i = -unitSize; i < m_WindowExtent.width + unitSize; i += unitSize)
	{
		SDL_RenderDrawLine(renderer, i + viewportOffset.x % unitSize, viewportOffset.y % unitSize, i + viewportOffset.x % unitSize, m_WindowExtent.height);
	}
	for (int32 i = -unitSize; i < m_WindowExtent.height + unitSize; i += unitSize)
	{
		SDL_RenderDrawLine(renderer, viewportOffset.x % unitSize, i + viewportOffset.y % unitSize, m_WindowExtent.width, i + viewportOffset.y % unitSize);
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

    using namespace std::chrono;
    auto lastTime = steady_clock::now();

    bool isRunning = true;
    SDL_Event event;

    bool isDragging = false;

	Vector2i lastMousePosition;

	m_WindowExtent.width = DEFAULT_WINDOW_WIDTH;
	m_WindowExtent.height = DEFAULT_WINDOW_HEIGHT;

	uint32 index = 0;

    while (isRunning)
    {

		auto currentTime = steady_clock::now();
        float deltaTime = duration_cast<duration<float>>(currentTime - lastTime).count();
        lastTime = currentTime;

		physicsEngine.Update();

		m_pScene->GetObject(1)->Rotate(60.f * deltaTime);

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
                        //m_ViewportOffset.x -= 10;
						//m_ViewportTransform[2][0] -= 10;
						m_pScene->GetObject(index)->Translate(glm::vec2(-1.0f, 0.0f));
                        break;
                    case SDLK_RIGHT:
                        //m_ViewportOffset.x += 10;
						//m_ViewportTransform[2][0] += 10;
						m_pScene->GetObject(index)->Translate(glm::vec2(1.0f, 0.0f));
                        break;
                    case SDLK_UP:
                        //m_ViewportOffset.y -= 10;
						//m_ViewportTransform[2][1] -= 10;
						m_pScene->GetObject(index)->Translate(glm::vec2(0.0f, -1.0f));
                        break;
                    case SDLK_DOWN:
                        //m_ViewportOffset.y += 10;
						//m_ViewportTransform[2][1] += 10;
						m_pScene->GetObject(index)->Translate(glm::vec2(0.0f, 1.0f));
                        break;
                    case SDLK_p:
						m_pScene->GetObject(index)->Rotate(10000.0f * deltaTime);
						break;
					case SDLK_n:
						index = ++index % m_pScene->GetObjects().size();
						break;
                }
            }

            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                m_WindowExtent.width = event.window.data1;
                m_WindowExtent.height = event.window.data2;
            }

            if (event.type == SDL_MOUSEWHEEL)
            {
                if (event.wheel.y != 0)
                {
                    if (SDL_GetModState() & KMOD_SHIFT)
                    {
                        //m_ViewportOffset.x -= event.wheel.y * 10;
						//m_ViewportTransform[2][0] -= event.wheel.y * 10;
                    }
                    else
                    {
                        //m_ViewportOffset.y -= event.wheel.y * 10;
						//m_ViewportTransform[2][1] -= event.wheel.y * 10;


						float scaleIncrement = 0.1f;

            			float scaleMultiplier = (event.wheel.y > 0) ? (1.0f - scaleIncrement) : (1.0f + scaleIncrement);

						m_ViewportScale = glm::vec2(scaleMultiplier, scaleMultiplier);

						m_ViewportTransform = glm::scale(glm::mat4(m_ViewportTransform), glm::vec3(m_ViewportScale, 1));
                    }
                }
            }


            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = true;
				lastMousePosition.x = event.button.x;
				lastMousePosition.y = event.button.y;

				auto pos = Viewport::TransformScreenSpaceToWorld(glm::vec2(lastMousePosition.x, lastMousePosition.y), m_ViewportTransform);

				std::cout << "(" << pos.x << "; " << pos.y << ")" << std::endl;
				//TODO: call some function to determine what's the polygon containing pos.

				auto polygon = m_pScene->PickObject(pos);
				if (polygon)
					polygon->SetColor({255, 0, 0, 255});
            }

            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = false;
            }

            if (isDragging && event.type == SDL_MOUSEMOTION)
            {
				Vector2i mouseDelta(event.motion.x - lastMousePosition.x, event.motion.y - lastMousePosition.y);

				//m_ViewportOffset.x += mouseDelta.x;
				m_ViewportTransform[2][0] += mouseDelta.x;
				lastMousePosition.x = event.motion.x;

                //m_ViewportOffset.y += mouseDelta.y;
				m_ViewportTransform[2][1] += mouseDelta.y;
				lastMousePosition.y = event.motion.y;
            }
        }

		//RenderScene(m_Renderer, m_ViewportOffset);
		RenderScene(m_Renderer, Vector2i(m_ViewportTransform[2][0], m_ViewportTransform[2][1]));
		m_pScene->Render(m_Renderer, m_ViewportTransform);

        SDL_RenderPresent(m_Renderer);
    }

	Shutdown();
}
