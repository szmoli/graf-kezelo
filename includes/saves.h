#pragma once

#include "typedefs.h"
#include "lists.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

char *get_date_time_str();
char *get_save_file_path(char *saves_dir, char *extension, char *time_str);
void check_and_make_saves_dir(char *saves_dir);
void save_vertices_and_selection(Vertex_List *list, FILE *save_file);
void save_edges(Edge_List *list, FILE *save_file);
void save_vertex_pointer_list(Vertex_Pointer_List *list, FILE *save_file);
void save_graph(Vertex_List *vertices, Edge_List *edges, char *vertices_save_path, char *edges_save_path, char *graph_save_path);
bool is_valid_graph_file(char *file_path, char *graph_file_estension);
char *get_date_time_str_from_file_path(char *file_path);
void load_vertices_and_selection(Vertex_List *vertices, Vertex_Pointer_List *selection, FILE *file, int *max_id);
void load_edges(Edge_List *edges, Vertex_List *vertices, FILE *file);
void load_graph(Vertex_List *vertices, Edge_List *edges, Vertex_Pointer_List *selection, char *vertices_save_path, char *edges_save_path, int *max_id);