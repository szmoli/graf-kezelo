#include "sdl_config.h"
#include <SDL.h>
#include <stdio.h>

int init_sdl(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *window_surface) {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("NHF", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL);

    if (window == NULL) {
        fprintf(stderr, "no window!\n");
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        fprintf(stderr, "no renderer!\n");
        return -1;
    }

    window_surface = SDL_GetWindowSurface(window);

    if (renderer == NULL) {
        fprintf(stderr, "no renderer!\n");
        return -1;
    }

    return 0;
}

void quit_sdl(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindowSurface(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
}