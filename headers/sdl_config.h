#pragma once
#include <SDL.h>

int init_sdl(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *window_surface);
void quit_sdl(SDL_Window *window, SDL_Renderer *renderer);