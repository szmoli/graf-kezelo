/**
 * @file linked_list.c
 * @author Szmoleniczki Ákos
 * @brief Ez a fájl a láncolt listák kezeléséhez szükséges függvényeket tartalmazza.
 * @version 0.1
 * @date 2023-11-09 
 */

#include "debugmalloc.h"
#include "typedefs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Létrehoz egy új láncolt listát. Memóriát nem szabadítja fel, az a hívó dolga.
 * 
 * @return Linked_List* Mutató a létrehozott listára.
 */
Linked_List *new_list() {
    Linked_List *list = (Linked_List *) malloc(sizeof(Linked_List));

    list->head_node = NULL;
    list->tail_node = NULL;
}

/**
 * @brief Létrehoz egy új listaelemet a megadott adat alapján. Memóriát nem szabadítja fel, az a hívó dolga.
 * 
 * @param data Mutató az adatra, amit a listaelem tartalmazni fog.
 * @return List_Node* Mutató a létrehozott listaelemre.
 */
List_Node *new_node(void *data) {
    List_Node *node = (List_Node *) malloc(sizeof(List_Node));

    node->data = data;
}

/**
 * @brief A megadott listaelemet hozzáfűzi a lista végére.
 * 
 * @param list A lista amihez hozzáfűz.
 * @param node A listaelem amit hozzáfűz.
 */
void list_push(Linked_List *list, List_Node *node) {
    node->next_node = NULL;
    
    if (list->head_node == NULL) list->head_node = node;
    if (list->tail_node != NULL) list->tail_node->next_node = node;

    list->tail_node = node;
}

/**
 * @brief Megkeresi és visszaadja a címét egy listaelemnek a megadott adat alapján.
 * 
 * @param list A lista amiben keres.
 * @param data Az adat, amit keres.
 * @return List_Node* Mutató a listaelemre, ha van találat. Ha nincs, akkor NULL.
 */
List_Node *get_node(Linked_List *list, void *data) {
    List_Node *p = list->head_node;
    
    while (p != NULL) {
        if (p->data == data) return p;

        p->next_node;
    }
    
    return NULL;
}

/**
 * @brief Felszabadít egy listaelemet és a hozzá tartozó adatot.
 * 
 * @param node A listaelem, amit felszabadít.
 */
void destroy_node(List_Node *node) {
    free(node->data);
    free(node);
    node = NULL;
}

/**
 * @brief Felszabadít egy listát és minden elemére meghívja a destroy_node függvényt.
 * @see destroy_node
 * 
 * @param list A lista, amit felszabadít.
 */
void destroy_list(Linked_List *list) {
    List_Node *p = list->head_node;
    List_Node *prev = NULL;

    while (p != NULL) {
        prev = p;
        p = p->next_node;
        destroy_node(prev);
    }

    free(list);
    list->head_node = NULL;
    list->tail_node = NULL;
    list = NULL;
}

/**
 * @brief A megadott listából eltávolít egy listaelemet és meghívja rá a destroy_node függvényt.
 * @see destroy_node
 * 
 * @param list A lista, amiből eltávolít.
 * @param node A listaelem, amit eltávolít.
 */
void list_pop(Linked_List *list, List_Node *node) {
    List_Node *p = list->head_node;
    List_Node *prev = NULL;

    while (p != NULL && p != node) {
        prev = p;
        p = p->next_node;
    }

    if (prev == NULL && p != NULL) { // head
        list->head_node = p->next_node;
    } else if (prev != NULL && p != NULL) { // normal
        prev->next_node = p->next_node;
    }

    destroy_node(node);
}

/**
 * @brief Kiírja a megadott lista elemeit a kiválasztott mód szerint. A kiírási módok a PRINT_MODES enumban találhatók.
 * @see PRINT_MODES
 * 
 * @param list A lista, aminek elemeit kiírja.
 * @param mode A kiválasztott kiírási mód.
 */
void print_list(Linked_List *list, PRINT_MODES mode) {
    List_Node *p = list->head_node;
    // printf("%p\n", p);

    while (p != NULL) {
        switch (mode) {
            case INT:
                printf("%u%s", *((int *)p->data), p->next_node == NULL ? "\n" : " -> ");
                break;
            case VERTEX_DATA:
                printf("%u%s", ((Vertex_Data *)p->data)->id, p->next_node == NULL ? "\n" : " -> ");
                break;
        }

        p = p->next_node;
    }
}

/**
 * @brief Létrehoz egy új adattagot a gráf egy pontjához.
 * 
 * @param id A gráf éppen aktuális azonosítója.
 * @return Vertex_Data* Mutató a létrehozott adatra.
 */
Vertex_Data *new_vertex_data(unsigned int *id) {
    Vertex_Data *vertex_data = (Vertex_Data *) malloc(sizeof(Vertex_Data));

    printf("id: %u\n", *id);

    vertex_data->id = (*id)++;

    return vertex_data;
}

