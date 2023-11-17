#include "debugmalloc.h"

#include <stdbool.h>
#include <memory.h>

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Vertex_Data {
    int id;
    bool selected;
} Vertex_Data;

typedef struct Vertex_Node {
    Vertex_Data vertex_data;
    struct Vertex_Node *next_node;
} Vertex_Node;

typedef struct Vertex_List {
    int size;
    Vertex_Node *head;
    Vertex_Node *tail;
} Vertex_List;

typedef struct Edge {
    Vertex_Node *from;
    Vertex_Node *to;
    bool directed;
} Edge;

typedef struct Edge_Node {
    Edge edge;
    struct Edge_Node *next_node;
} Edge_Node;

typedef struct Edge_List {
    int size;
    Edge_Node *head;
    Edge_Node *tail;
} Edge_List;

typedef struct Vertex_Pointer_Node {
    Vertex_Node *vertex_node;
    struct Vertex_Pointer_Node *next_node;
} Vertex_Pointer_Node;

typedef struct Vertex_Pointer_List {
    int size;
    Vertex_Pointer_Node *head;
    Vertex_Pointer_Node *tail;
} Vertex_Pointer_List;

Vertex_Node *new_vertex_node() {
    return (Vertex_Node *) malloc(sizeof(Vertex_Node));
}

Edge_Node *new_edge_node() {
    return (Edge_Node *) malloc(sizeof(Edge_Node));
}

Vertex_Pointer_Node *new_vertex_pointer_node() {
    return (Vertex_Pointer_Node *) malloc(sizeof(Vertex_Pointer_Node));
}

Vertex_List *new_vertex_list() {
    Vertex_List *list = (Vertex_List *) malloc(sizeof(Vertex_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Edge_List *new_edge_list() {
    Edge_List *list = (Edge_List *) malloc(sizeof(Edge_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Vertex_Pointer_List *new_vertex_pointer_list() {
    Vertex_Pointer_List *list = (Vertex_Pointer_List *) malloc(sizeof(Vertex_Pointer_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void destroy_vertex_list(Vertex_List *list) {
    Vertex_Node *iterator = list->head;
    Vertex_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
        free(previous);
    }

    free(list);
    list = NULL;
}

void clear_vertex_list(Vertex_List *list) {
        Vertex_Node *iterator = list->head;
    Vertex_Node *previous = NULL;
    
    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
        free(previous);
        previous = NULL;
    }

    free(list);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void destroy_edge_list(Edge_List *list) {
    Edge_Node *iterator = list->head;
    Edge_Node *previous = NULL;
    
    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
        free(previous);
    }

    free(list);
    list = NULL;
}

void clear_edge_list(Edge_List *list) {
    Edge_Node *iterator = list->head;
    Edge_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
        free(previous);
        previous = NULL;
    }

    free(list);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void destroy_vertex_pointer_list(Vertex_Pointer_List *list) {
    Vertex_Pointer_Node *iterator = list->head;
    Vertex_Pointer_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
        free(previous);
    }

    free(list);
    list = NULL;
}

void clear_vertex_pointer_list(Vertex_Pointer_List *list) {
    Vertex_Pointer_Node *iterator = list->head;
    Vertex_Pointer_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
        free(previous);
        previous = NULL;
    }

    free(list);
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void vertex_list_push(Vertex_List *list, Vertex_Node *node) {
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    node->next_node = NULL;
    list->size++;
}

void edge_list_push(Edge_List *list, Edge_Node *node) {
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    node->next_node = NULL;
    list->size++;
}

void vertex_pointer_list_push(Vertex_Pointer_List *list, Vertex_Pointer_Node *node) {
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    node->next_node = NULL;
    list->size++;
}

void vertex_list_pop(Vertex_List *list, Vertex_Node *node) {
    Vertex_Node *iterator = list->head;
    Vertex_Node *previous = NULL;

    if (iterator == NULL) return;

    while (iterator != NULL && iterator != node) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (iterator == list->head) {
        list->head = iterator->next_node;
    } else if (iterator != NULL) {
        previous->next_node = iterator->next_node;
    }

    list->size--;
    free(iterator);
    iterator = NULL;
}

void edge_list_pop(Edge_List *list, Edge_Node *node) {
    Edge_Node *iterator = list->head;
    Edge_Node *previous = NULL;

    if (iterator == NULL) return;

    while (iterator != NULL && iterator != node) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (iterator == list->head) {
        list->head = iterator->next_node;
    } else if (iterator != NULL) {
        previous->next_node = iterator->next_node;
    }

    list->size--;
    free(iterator);
    iterator = NULL;
}

void vertex_pointer_list_pop(Vertex_Pointer_List *list, Vertex_Pointer_Node *node) {
    Vertex_Pointer_Node *iterator = list->head;
    Vertex_Pointer_Node *previous = NULL;

    if (iterator == NULL) return;

    while (iterator != NULL && iterator != node) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (iterator == list->head) {
        list->head = iterator->next_node;
    } else if (iterator != NULL) {
        previous->next_node = iterator->next_node;
    }

    list->size--;
    free(iterator);
    iterator = NULL;
}

void print_vertex_list(Vertex_List *list) {
    Vertex_Node *iterator = list->head;

    if (iterator == NULL) return;

    while (iterator != NULL) {
        printf("%d (%p)%s", iterator->vertex_data.id, iterator, iterator->next_node == NULL ? "\n" : " -> ");
        iterator = iterator->next_node;
    }
}

void print_edge_list(Edge_List *list) {
    Edge_Node *iterator = list->head;

    if (iterator == NULL) return;

    while (iterator != NULL) {
        printf("(%d (%p)%s%d (%p)%s)", iterator->edge.from->vertex_data.id, iterator->edge.from, iterator->edge.directed ? " -> " : " <-> ", iterator->edge.to->vertex_data.id, iterator->edge.from, iterator->next_node == NULL ? "\n" : " -> ");
        iterator = iterator->next_node;
    }
}

void print_vertex_pointer_list(Vertex_Pointer_List *list) {
    Vertex_Pointer_Node *iterator = list->head;

    if (iterator == NULL) return;

    while (iterator != NULL) {
        printf("%d (%p)%s", iterator->vertex_node->vertex_data.id, iterator->vertex_node, iterator->next_node == NULL ? "\n" : " -> ");
        iterator = iterator->next_node;
    }
}

int main(void) {
    Vertex_List *vertices = new_vertex_list();
    Vertex_Pointer_List *selection = new_vertex_pointer_list();
    Edge_List *edges = new_edge_list();

    vertex_list_push(vertices, new_vertex_node());
    edge_list_push(edges, new_edge_node());
    vertex_pointer_list_push(selection, new_vertex_pointer_node());
    vertex_list_pop(vertices, vertices->head);
    edge_list_pop(edges, edges->head);
    vertex_pointer_list_pop(selection, selection->head);

    destroy_edge_list(edges);
    destroy_vertex_pointer_list(selection);
    destroy_vertex_list(vertices);

    return 0;
}