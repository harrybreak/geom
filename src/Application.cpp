#include "Application.hpp" 
#include "Scene.hpp"
#include "Vector2.hpp"
#include "glm/fwd.hpp"
#include <string>
#include <limits>



//TTF_Font* font = nullptr;

Application::Application(Scene* scene) : 
m_Window(nullptr), m_Renderer(nullptr), /*m_ViewportOffset(),*/ m_WindowExtent(), m_pScene(scene), m_ViewportScale(2, 2), m_ViewportTransform(1)
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
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Application::RenderScene(SDL_Renderer* renderer, Vector2i viewportOffset)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	DrawGrid(renderer, viewportOffset);


	SDL_Color color;
	color.r = 1;
	color.g = 1;
	color.b = 1;
	color.a = 1;
	DrawLine(renderer, viewportOffset.x + 20, viewportOffset.y + 20, viewportOffset.x + 80, viewportOffset.y + 56, color);

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
    // Set the drawing color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Draw the line
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    // Reset drawing color (optional)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void Application::Run()
{
	m_ViewportTransform = glm::scale(glm::mat4(m_ViewportTransform), glm::vec3(m_ViewportScale, 1));
	Init();


    bool isRunning = true;
    SDL_Event event;

    bool isDragging = false;

	Vector2i lastMousePosition;

	m_WindowExtent.width = DEFAULT_WINDOW_WIDTH;
	m_WindowExtent.height = DEFAULT_WINDOW_HEIGHT;

    while (isRunning)
    {
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
						m_pScene->GetObject(0)->Translate(glm::vec2(-1.0f, 0.0f));
                        break;
                    case SDLK_RIGHT:
                        //m_ViewportOffset.x += 10;
						//m_ViewportTransform[2][0] += 10;
						m_pScene->GetObject(0)->Translate(glm::vec2(1.0f, 0.0f));
                        break;
                    case SDLK_UP:
                        //m_ViewportOffset.y -= 10;
						//m_ViewportTransform[2][1] -= 10;
						m_pScene->GetObject(0)->Translate(glm::vec2(0.0f, -1.0f));
                        break;
                    case SDLK_DOWN:
                        //m_ViewportOffset.y += 10;
						//m_ViewportTransform[2][1] += 10;
						m_pScene->GetObject(0)->Translate(glm::vec2(0.0f, 1.0f));
                        break;
                    case SDLK_p:
						m_pScene->GetObject(0)->Rotate(5.0f);
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
						m_ViewportTransform[2][0] -= event.wheel.y * 10;
                    }
                    else
                    {
                        //m_ViewportOffset.y -= event.wheel.y * 10;
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
