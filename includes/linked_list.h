#pragma once

#include "typedefs.h"

List *new_list();
Node *new_node(void *data);
void list_push(List *list, Node *node);
Node *get_node(List *list, void *data);
void destroy_node(Node *node);
void destroy_list(List *list);
void list_pop(List *list, Node *node);
void print_list(List *list, MODES mode);
Vertex_Data *new_vertex_data(unsigned int *id);