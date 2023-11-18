/**
 * @brief Listaműveletek
 */

#include "lists.h"

/**
 * @brief Létrehoz a memóriában egy új gráf pont listaelemet.
 * 
 * @return Vertex_Node* A létrehozott listaelem címe
 */
Vertex_Node *new_vertex_node() {
    return (Vertex_Node *) malloc(sizeof(Vertex_Node));
}

/**
 * @brief Létrehoz a memóriában egy új gráf él listaelemet.
 * 
 * @return Edge_Node* A létrehozott listaelem címe
 */
Edge_Node *new_edge_node() {
    return (Edge_Node *) malloc(sizeof(Edge_Node));
}

/**
 * @brief Létrehoz a memóriában egy új gráf pont mutató listaelemet.
 * 
 * @return Vertex_Pointer_Node* A létrehozott listaelem címe
 */
Vertex_Pointer_Node *new_vertex_pointer_node() {
    return (Vertex_Pointer_Node *) malloc(sizeof(Vertex_Pointer_Node));
}

/**
 * @brief Létrehoz a memóriában egy új gráf pont listát.
 * 
 * @return Vertex_List* A létrehozott lista címe.
 */
Vertex_List *new_vertex_list() {
    Vertex_List *list = (Vertex_List *) malloc(sizeof(Vertex_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * @brief Létrehoz a memóriában egy új gráf él listát.
 * 
 * @return Edge_List* A létrehozott lista címe.
 */
Edge_List *new_edge_list() {
    Edge_List *list = (Edge_List *) malloc(sizeof(Edge_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * @brief Létrehoz a memóriában egy új gráf pont mutató listát.
 * 
 * @return Vertex_Pointer_List* A létrehozott lista címe.
 */
Vertex_Pointer_List *new_vertex_pointer_list() {
    Vertex_Pointer_List *list = (Vertex_Pointer_List *) malloc(sizeof(Vertex_Pointer_List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/**
 * @brief Felszabadítja a megadott gráf pont listát
 * 
 * @param list Felszabadítandó lista címe
 */
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

/**
 * @brief Kiüríti a megadott gráf pont listát
 * 
 * @param list Kiürítendő lista címe
 */
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

/**
 * @brief Felszabadítja a megadott gráf él listát
 * 
 * @param list Felszabadítandó lista címe
 */
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

/**
 * @brief Kiüríti a megadott gráf él listát
 * 
 * @param list Kiürítendő lista címe
 */
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

/**
 * @brief Felszabadítja a megadott gráf pont mutató listát
 * 
 * @param list Felszabadítandó lista címe
 */
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

/**
 * @brief Kiüríti a megadott gráf pont mutató listát
 * 
 * @param list Kiürítendő lista címe
 */
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

/**
 * @brief Hozzáad a megadott lista végéhez egy listaelemet.
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void vertex_list_push(Vertex_List *list, Vertex_Node *node) {
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    node->next_node = NULL;
    list->size++;
}

/**
 * @brief Hozzáad a megadott lista végéhez egy listaelemet.
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void edge_list_push(Edge_List *list, Edge_Node *node) {
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    node->next_node = NULL;
    list->size++;
}

/**
 * @brief Hozzáad a megadott lista végéhez egy listaelemet.
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void vertex_pointer_list_push(Vertex_Pointer_List *list, Vertex_Pointer_Node *node) {
    if (list->head == NULL) list->head = node;
    if (list->tail != NULL) list->tail->next_node = node;    
    list->tail = node;
    node->next_node = NULL;
    list->size++;
}

/**
 * @brief Kitörli a megadott listából a megadott listaelemet
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
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

/**
 * @brief Kitörli a megadott listából a megadott listaelemet
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
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

/**
 * @brief Kitörli a megadott listából a megadott listaelemet
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
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

/**
 * @brief Kiírja a megadott lista összes elemét
 * 
 * @param list Lista címe
 */
void print_vertex_list(Vertex_List *list) {
    Vertex_Node *iterator = list->head;

    if (iterator == NULL) return;

    while (iterator != NULL) {
        printf("%d (%p)%s", iterator->vertex_data.id, iterator, iterator->next_node == NULL ? "\n" : " -> ");
        iterator = iterator->next_node;
    }

    // printf("%p\n", list->tail->next_node);
}

/**
 * @brief Kiírja a megadott lista összes elemét
 * 
 * @param list Lista címe
 */
void print_edge_list(Edge_List *list) {
    Edge_Node *iterator = list->head;

    if (iterator == NULL) return;

    while (iterator != NULL) {
        printf("(%d (%p)%s%d (%p)%s)", iterator->edge.from->vertex_data.id, iterator->edge.from, iterator->edge.directed ? " -> " : " <-> ", iterator->edge.to->vertex_data.id, iterator->edge.from, iterator->next_node == NULL ? "\n" : " -> ");
        iterator = iterator->next_node;
    }
}

/**
 * @brief Kiírja a megadott lista összes elemét
 * 
 * @param list Lista címe
 */
void print_vertex_pointer_list(Vertex_Pointer_List *list) {
    Vertex_Pointer_Node *iterator = list->head;

    if (iterator == NULL) return;

    while (iterator != NULL) {
        printf("%d (%p)%s", iterator->vertex_node->vertex_data.id, iterator->vertex_node, iterator->next_node == NULL ? "\n" : " -> ");
        iterator = iterator->next_node;
    }
}