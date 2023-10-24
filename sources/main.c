#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "constants.h"
#include "debugmalloc.h"
#include "sdl_config.h"
#include "graph.h"

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    bool quit = false;
    
    SDL_Window *window = SDL_CreateWindow("NHF", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    if (window == NULL) {
        printf("no window\n");
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("no renderer\n");
        return -1;
    }
        
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if (window_surface == NULL) {
        printf("no window surface\n");
        return -1;
    }

    int x = 0;
    int y = 0;
    int radius = 10;

    

    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                quit_sdl(window, renderer);
                break;
            
            default:
                x++;
                y++;
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );
                SDL_Rect fillRect = { x - radius, y - radius, 2 * radius, 2 * radius };    
                SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
                SDL_RenderFillRect( renderer, &fillRect );
                SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderDrawPoint(renderer, x, y);
                SDL_RenderPresent(renderer);
                break;
        }
    }
    
    return 0;
}