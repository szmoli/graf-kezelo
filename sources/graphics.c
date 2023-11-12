#include "graphics.h"

bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_EVERYTHING);

    *window = SDL_CreateWindow("Gráfkezelő", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (*window == NULL) {
        fprintf(stderr, "%s: no window\n", __func__);
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*renderer == NULL) {
        SDL_DestroyRenderer(*renderer);
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
    }

    if (*renderer == NULL) {
        fprintf(stderr, "%s: no renderer\n", __func__);
        return false;
    }

    *window_surface = SDL_GetWindowSurface(*window);

    if (*window_surface == NULL) {
        fprintf(stderr, "%s: no window surface\n", __func__);
        return false;        
    }

    return true;
}

void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop) {
    *loop = false;
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindowSurface(*window);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}