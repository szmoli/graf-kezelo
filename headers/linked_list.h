#pragma once

#include "debugmalloc.h"

#include "globals.h"

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

struct Dynamic_Array;

typedef struct Vertex_Data {
    int id;
    unsigned int index;
    unsigned int radius;
    int x, y;
} Vertex_Data;

typedef struct List_Node {
    Vertex_Data *vertex_data;
    struct List_Node *prev_node;
    struct List_Node *next_node;
} List_Node;

typedef struct Linked_List {
    int size;
    List_Node *head_node;
} Linked_List;

List_Node *alloc_list_node();
void destroy_list_node(List_Node *list_node);
void new_list_node(Linked_List *linked_list);
Vertex_Data *alloc_vertex_data();
void free_vertex_data(Vertex_Data *vertex_data);
Vertex_Data *new_vertex_data(unsigned int radius, int x, int y);
Linked_List *alloc_linked_list();
void destroy_linked_list(Linked_List *linked_list);
Linked_List *new_list_with_head();
List_Node *get_last_node(Linked_List *linked_list);
void append_list_node(Linked_List *linked_list, List_Node *list_node);
void delete_list_node(Linked_List *linked_list, List_Node *list_node);
void print_linked_list(Linked_List *linked_list);
List_Node *get_list_node(Linked_List *linked_list, unsigned int id);
Linked_List *new_list_empty();
void list_push(Linked_List *linked_list, List_Node *list_node);
void list_pop(Linked_List *linked_list, List_Node *list_node);
List_Node *copy_list_node(List_Node *list_node);
void create_edge(List_Node *a, List_Node *b);