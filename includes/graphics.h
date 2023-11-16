#pragma once

#include "constants.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "typedefs.h"
#ifdef DEBUG
#include "linked_list.h"
#endif

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer);
void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop);
void transfrom_point(Point *point, SDL_Surface *window_surface);
void draw_main_circle(SDL_Surface *window_surface, SDL_Renderer *renderer, int radius, Point center);
void set_vertices_coords(List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offse, int y_offset);
void draw_vertices(List *vertices, SDL_Renderer *renderer, int radius);
int get_max_size(SDL_Surface *window_surface);
Node *get_clicked_node(SDL_Event *event, List *vertices, int radius);
void print_node(Node *node, MODES mode);
void select_node(Node* node);
void deselect_original_node(Node* node);
void toggle_node_selection(Node* node);
void deselect_node(Node* node);
int get_radius(int max_size, double mode_multiplier, double zoom_multiplier);
void draw_edges(Array *neighbour_arr, SDL_Renderer *renderer);