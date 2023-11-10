#pragma once

#include "typedefs.h"

List *new_list();
List_Node *new_node(void *data);
void list_push(List *list, List_Node *node);
List_Node *get_node(List *list, void *data);
void destroy_node(List_Node *node);
void destroy_list(List *list);
void list_pop(List *list, List_Node *node);
void print_list(List *list, PRINT_MODES mode);
Vertex_Data *new_vertex_data(unsigned int *id);