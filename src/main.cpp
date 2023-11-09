#include "graphics/graphics.h"

using namespace std;

int main()
{
    bool quit = false;
    SDL_Event event;
    int x = 200;
    int y = 200;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * screen = SDL_CreateWindow("Training with SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 854, 480, 0);

    SDL_Renderer *  renderer = SDL_CreateRenderer(screen, -1, 0);

    SDL_Surface * image = SDL_LoadBMP_RW(SDL_RWFromFile("assets/asprite.bmp", "r+"), 1);

    

    while (!quit) {
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
        }
    }

    SDL_Quit();

    return 0;
}