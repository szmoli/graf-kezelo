/**
 * @brief Ez a fájl a láncolt listák kezeléséhez szükséges függvényeket tartalmazza.
 */

#include "debugmalloc.h"
#include "typedefs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Létrehoz egy új láncolt listát. Memóriát nem szabadítja fel, az a hívó dolga.
 * 
 * @return List* Mutató a létrehozott listára.
 */
List *new_list() {
    List *list = (List *) malloc(sizeof(List));

    list->size = 0;
    list->head_node = NULL;
    list->tail_node = NULL;
}

/**
 * @brief Létrehoz egy új listaelemet a megadott adat alapján. Memóriát nem szabadítja fel, az a hívó dolga.
 * 
 * @param data Mutató az adatra, amit a listaelem tartalmazni fog.
 * @return Node* Mutató a létrehozott listaelemre.
 */
Node *new_node(void *data) {
    Node *node = (Node *) malloc(sizeof(Node));

    node->data = data;
}

/**
 * @brief A megadott listaelemet hozzáfűzi a lista végére.
 * 
 * @param list A lista amihez hozzáfűz.
 * @param node A listaelem amit hozzáfűz.
 */
void list_push(List *list, Node *node) {
    node->next_node = NULL;
    
    if (list->head_node == NULL) list->head_node = node;
    if (list->tail_node != NULL) list->tail_node->next_node = node;

    list->size++;
    list->tail_node = node;
}

/**
 * @brief Megkeresi és visszaadja a címét egy listaelemnek a megadott adat alapján.
 * 
 * @param list A lista amiben keres.
 * @param data Az adat, amit keres.
 * @return Node* Mutató a listaelemre, ha van találat. Ha nincs, akkor NULL.
 */
Node *get_node(List *list, void *data) {
    Node *p = list->head_node;
    
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
 * @param destroy_data Felszabadítsa-e az adattagot is?
 */
void destroy_node(Node *node, bool destroy_data) {
    if (destroy_data) {
        free(node->data);
        //printf("data freed\n");
    } else {
        node->data = NULL;
    }
    
    free(node);
    //printf("node freed\n");
    node = NULL;
}

/**
 * @brief Felszabadít egy listát és minden elemére meghívja a destroy_node függvényt.
 * @see destroy_node
 * 
 * @param list A lista, amit felszabadít.
 */
void destroy_list(List *list, bool destroy_data) {
    Node *p = list->head_node;
    Node *prev = NULL;

    while (p != NULL) {
        prev = p;
        p = p->next_node;
        destroy_node(prev, destroy_data);
    }

    list->head_node = NULL;
    list->tail_node = NULL;
    free(list);
    list = NULL;
}

/**
 * @brief A megadott listából eltávolít egy listaelemet és meghívja rá a destroy_node függvényt.
 * @see destroy_node
 * 
 * @param list A lista, amiből eltávolít.
 * @param node A listaelem, amit eltávolít.
 */
void list_pop(List *list, Node *node, bool destroy_data) {
    Node *p = list->head_node;
    Node *prev = NULL;

    while (p != NULL && p != node) {
        prev = p;
        p = p->next_node;
    }

    if (prev == NULL && p != NULL) { // head
        list->head_node = p->next_node;
    } else if (prev != NULL && p != NULL) { // normal
        prev->next_node = p->next_node;
    }

    list->size--;

    destroy_node(node, destroy_data);
}

/**
 * @todo Kell ez egyáltalán?
 * @brief 
 * 
 * @param list 
 * @param destroy_data 
 */
void list_clear(List *list, bool destroy_data) {
    Node *p = list->head_node;
    Node *prev = NULL;

    while (p != NULL) {
        list_pop(list, p, destroy_data);
        p = p->next_node;
    }
}

/**
 * @brief Kiírja a megadott lista elemeit a kiválasztott mód szerint. A kiírási módok a MODES enumban találhatók.
 * @see MODES
 * 
 * @param list A lista, aminek elemeit kiírja.
 * @param mode A kiválasztott kiírási mód.
 */
void print_list(List *list, MODES mode) {
    Node *p = list->head_node;
    // printf("%p\n", p);

    while (p != NULL) {
        // switch (mode) {
        //     case VERTEX_DATA_POINTER:
        //         printf("%u (%p)%s", *(int *)(*((Vertex_Data **) p->data)), *((Vertex_Data *)(p->data)), p->next_node == NULL ? "\n" : " -> "); // hát ez nagyon szép lett
        //         break;
        //     case VERTEX_DATA:
        //         printf("%u (%p)%s", ((Vertex_Data *) p->data)->id, p->data, p->next_node == NULL ? "\n" : " -> ");
        //         break;
        // }

        print_node(p, mode);

        p = p->next_node;
    }
}

/**
 * @brief Kiírja a megadott listaelem adattagját a megadott üzemmód szerint formázva.
 * 
 * @param node Listaelem
 * @param mode Üzemmód
 */
void print_node(Node *node, MODES mode) {
    switch (mode) {
        case VERTEX_DATA_POINTER:
            printf("%u (%p)%s", *(int *)(*((Vertex_Data **) node->data)), *((Vertex_Data *)(node->data)), node->next_node == NULL ? "\n" : " -> "); // hát ez nagyon szép lett
            break;
        case VERTEX_DATA:
            printf("%u (%p)%s", ((Vertex_Data *) node->data)->id, node->data, node->next_node == NULL ? "\n" : " -> ");
            break;
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

    //printf("id: %u\n", *id);

    vertex_data->id = (*id)++;
    vertex_data->selected = false;

    return vertex_data;
}

