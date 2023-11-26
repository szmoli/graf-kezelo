#pragma once

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
void create_vertex(Vertex_List *vertices, int *vertex_id, int radius, int vertex_red, int vertex_green, int vertex_blue, int vertex_alpha);
void set_vertices_coords(Vertex_List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offset, int y_offset, double main_circle_radius_multiplier);
int get_radius(int max_size, double mode_multiplier, double zoom_multiplier);
void draw_vertices(Vertex_List *vertices, SDL_Renderer *renderer);
Vertex_Node *get_clicked_node(SDL_Event *event, Vertex_List *vertices);
void select_vertex(Vertex_Pointer_List *selection, Vertex_Node *vertex_node, int selected_red, int selected_green, int selected_blue, int selected_alpha);
void unselect_vertex(Vertex_Pointer_List *selection, Vertex_Pointer_Node *vertex_pointer_node, int vertex_red, int vertex_green, int vertex_blue, int vertex_alpha);
void create_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, int edge_red, int edge_green, int edge_blue, int edge_alpha, int edge_width);
void draw_edges(Edge_List *edges, SDL_Renderer *renderer);
Edge_Node *get_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from);
void toggle_select_edges(Edge_List *edges, Vertex_Node *vertex_node, int edge_red, int edge_green, int edge_blue, int edge_alpha);
void unvisit_vertices(Vertex_List *vertices);
void depth_first_traverse(Vertex_List *vertices, Vertex_Node *vertex_node, Edge_List *edges, Vertex_Pointer_List *selection, int selected_red, int selected_green, int selected_blue, int selected_alpha);
void breadth_first_traverse(Vertex_List *vertices, Vertex_Node *vertex_node, Edge_List *edges, Vertex_Pointer_List *selection, int selected_red, int selected_green, int selected_blue, int selected_alpha);