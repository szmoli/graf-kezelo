#pragma once

#include "SDL.h"

#include <stdbool.h>
#include <stdio.h>

bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer);
void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop);