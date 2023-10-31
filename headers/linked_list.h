#pragma once

#include "debugmalloc.h"

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

typedef struct Vertex_Data {
    unsigned int id;
} Vertex_Data;

typedef struct List_Node {
    void *node_data;
    struct List_Node *prev_node;
    struct List_Node *next_node;
} List_Node;

typedef struct Linked_List {
    int size;
    List_Node *head_node;
} Linked_List;

List_Node *alloc_list_node();
void free_list_node(List_Node *list_node);
void new_list_node(Linked_List *linked_list, Vertex_Data *node_data);
Vertex_Data *alloc_vertex_data();
void free_vertex_data(Vertex_Data *vertex_data);
Vertex_Data *new_vertex_data(int id);
Linked_List *alloc_linked_list();
void free_linked_list(Linked_List *linked_list);
Linked_List *new_linked_list();
List_Node *get_last_node(Linked_List *linked_list);
void append_list_node(Linked_List *linked_list, List_Node *list_node);
void delete_list_node(List_Node *list_node);
void print_linked_list(Linked_List *linked_list);
List_Node *get_list_node(Linked_List *linked_list, Vertex_Data *vertex_data);