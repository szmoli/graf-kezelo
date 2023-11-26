#include "lists.h"

Vertex_Node *new_vertex_node() {
    Vertex_Node *node = (Vertex_Node *) malloc(sizeof(Vertex_Node));    
    node->next_node = NULL;
    return node;
}

Edge_Node *new_edge_node() {
    Edge_Node *node = (Edge_Node *) malloc(sizeof(Edge_Node));    
    node->next_node = NULL;
    return node;
}

Vertex_Pointer_Node *new_vertex_pointer_node() {
    Vertex_Pointer_Node *node = (Vertex_Pointer_Node *) malloc(sizeof(Vertex_Pointer_Node));
    node->next_node = NULL;
    return node;
}

Vertex_List *new_vertex_list() {
    Vertex_List *list = (Vertex_List *) malloc(sizeof(Vertex_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

Edge_List *new_edge_list() {
    Edge_List *list = (Edge_List *) malloc(sizeof(Edge_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

Vertex_Pointer_List *new_vertex_pointer_list() {
    Vertex_Pointer_List *list = (Vertex_Pointer_List *) malloc(sizeof(Vertex_Pointer_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
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

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void vertex_list_push(Vertex_List *list, Vertex_Node *node) {
    Vertex_Node *iterator = list->head;
    Vertex_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (list->head == NULL) list->head = node;
    else if (previous == list->head && list->head != NULL) list->head->next_node = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    list->size++;
}

void edge_list_push(Edge_List *list, Edge_Node *node) {
    Edge_Node *iterator = list->head;
    Edge_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (list->head == NULL) list->head = node;
    else if (previous == list->head && list->head != NULL) list->head->next_node = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    list->size++;
}

void vertex_pointer_list_push(Vertex_Pointer_List *list, Vertex_Pointer_Node *node) {
    Vertex_Pointer_Node *iterator = list->head;
    Vertex_Pointer_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (list->head == NULL) list->head = node;
    else if (previous == list->head && list->head != NULL) list->head->next_node = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    list->size++;
}

void vertex_list_pop(Vertex_List *list, Vertex_Node *node) {
    Vertex_Node *iterator = list->head;
    Vertex_Node *previous = NULL;

    if (node == NULL) return;

    while (iterator != NULL && iterator != node) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (iterator == NULL) {
        return;
    }

    if (previous != NULL) {
        previous->next_node = iterator->next_node;
    }

    if (previous == NULL) {
        list->head = iterator->next_node;
    }

    if (iterator->next_node == NULL) {
        list->tail = previous;
    }

    list->size--;
    free(iterator);
    iterator = NULL;
}

void edge_list_pop(Edge_List *list, Edge_Node *node) {
    Edge_Node *iterator = list->head;
    Edge_Node *previous = NULL;

    if (node == NULL) return;

    while (iterator != NULL && iterator != node) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (iterator == NULL) {
        return;
    }

    if (previous != NULL) {
        previous->next_node = iterator->next_node;
    }

    if (previous == NULL) {
        list->head = iterator->next_node;
    }

    if (iterator->next_node == NULL) {
        list->tail = previous;
    }

    list->size--;
    free(iterator);
    iterator = NULL;
}

void vertex_pointer_list_pop(Vertex_Pointer_List *list, Vertex_Pointer_Node *node) {
    Vertex_Pointer_Node *iterator = list->head;
    Vertex_Pointer_Node *previous = NULL;

    if (node == NULL) return;

    while (iterator != NULL && iterator != node) {
        previous = iterator;
        iterator = iterator->next_node;
    }

    if (iterator == NULL) {
        return;
    }

    if (previous != NULL) {
        previous->next_node = iterator->next_node;
    }

    if (previous == NULL) {
        list->head = iterator->next_node;
    }

    if (iterator->next_node == NULL) {
        list->tail = previous;
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
        printf("(%d (%p)%s%d (%p)%s)", iterator->edge.from->vertex_data.id, iterator->edge.from, " -> ", iterator->edge.to->vertex_data.id, iterator->edge.from, "\n");
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

Vertex_Pointer_Node *get_vertex_pointer_node(Vertex_Pointer_List *list, Vertex_Node *vertex_node) {
    Vertex_Pointer_Node *iterator = list->head;

    while (iterator != NULL && iterator->vertex_node != vertex_node) {
        iterator = iterator->next_node;
    }

    return iterator;
}

Vertex_Node *get_vertex_node_by_id(Vertex_List *list, int id) {
    Vertex_Node *iterator = list->head;

    while (iterator != NULL && iterator->vertex_data.id != id) {
        iterator = iterator->next_node;
    }
    
    return iterator;
}