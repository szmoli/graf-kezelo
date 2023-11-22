#pragma once

#include "constants.h"
#include "debugmalloc.h"
#include "typedefs.h"
#include "lists.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer);
void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop);
void transfrom_point(Point *point, SDL_Surface *window_surface);
int get_max_size(SDL_Surface *window_surface);
void create_vertex(Vertex_List *vertices, size_t vertex_id, int radius);
void set_vertices_coords(Vertex_List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offset, int y_offset);
int get_radius(int max_size, double mode_multiplier, double zoom_multiplier);
void draw_vertices(Vertex_List *vertices, SDL_Renderer *renderer);
Vertex_Node *get_clicked_node(SDL_Event *event, Vertex_List *vertices);
void select_vertex(Vertex_Pointer_List *selection, Vertex_Node *vertex_node);
void unselect_vertex(Vertex_Pointer_List *selection, Vertex_Pointer_Node *vertex_pointer_node);
void create_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, bool directed);
void draw_edges(Edge_List *edges, SDL_Renderer *renderer);
Edge_Node *get_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from);