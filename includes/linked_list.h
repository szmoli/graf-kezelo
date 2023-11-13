#pragma once

#include "typedefs.h"
#include <stdbool.h>

List *new_list();
Node *new_node(void *data);
void list_push(List *list, Node *node);
Node *get_node(List *list, void *data);
void destroy_node(Node *node, bool destroy_data);
void destroy_list(List *list, bool destroy_data);
void list_pop(List *list, Node *node, bool destroy_data);
void print_list(List *list, MODES mode);
Vertex_Data *new_vertex_data(unsigned int *id);
void list_clear(List *list, bool destroy_data);
void print_node(Node *node, MODES mode);