#pragma once

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "typedefs.h"
#include "constants.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer);
void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop);
void transfrom_point(Point *point, SDL_Surface *window_surface);
void draw_main_circle(SDL_Surface *window_surface, SDL_Renderer *renderer, int x, int y);
void set_vertices_coords(List *vertexes, SDL_Surface *window_surface);
void draw_vertices(List *vertexes, SDL_Surface *window_surface, SDL_Renderer *renderer);
int get_max_size(SDL_Surface *window_surface);
Node *get_clicked_node(SDL_Surface *window_surface, SDL_Event *event, List *vertices);
void print_node(Node *node, MODES mode);
void select_node(Node* node);
void deselect_node(Node* node);
void toggle_node_selection(Node* node);