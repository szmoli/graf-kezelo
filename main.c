#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "debugmalloc.h"
#include "sdl_config.h"

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *window_surface = NULL;
    bool quit = false;

    if (init_sdl(window, renderer, window_surface) == -1) {
        return -1;
    }

    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                quit_sdl(window, renderer);
                break;
            
            default:
                
                break;
        }
    }
    
    return 0;
}