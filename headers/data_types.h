#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct List_Node;

typedef struct Vertex_Data {
    int id;
    unsigned int index;
    unsigned int radius;
    int x, y;
} Vertex_Data;

typedef struct List_Node {
    Vertex_Data *vertex_data;
    struct List_Node *next_node;
} List_Node;

typedef struct Linked_List {
    int size;
    List_Node *head_node;
    List_Node *tail_node;
} Linked_List;

typedef struct Dynamic_Array {
    size_t size;
    struct Linked_List** array;
} Dynamic_Array;