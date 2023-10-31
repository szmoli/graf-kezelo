#include "linked_list.h"

/*
    csak memóriát foglal!
*/
Vertex_Data *alloc_vertex_data() {
    return (Vertex_Data *) malloc(sizeof(Vertex_Data));
}

void free_vertex_data(Vertex_Data *vertex_data) {
    free(vertex_data);
    vertex_data = NULL;
}

/*
    létrehoz egy új vertex_data-t a megadott paraméterek alapján

    csak memóriát foglal!
*/
Vertex_Data *new_vertex_data(int id) {
    Vertex_Data *vertex_data = alloc_vertex_data();

    vertex_data->id = id;

    return vertex_data;
}

// csak foglalja a memóriát, nem szabadítja fel!
List_Node *alloc_list_node() {
    return (List_Node *) malloc(sizeof(List_Node));
}

/*
    free_vertex_data

    felszabadítja a memóriát
*/
void free_list_node(List_Node *list_node) {
    free_vertex_data(list_node->node_data);

    free(list_node);
    list_node = NULL;
}

/*
    létrehoz egy új node-ot ami a megadott adatott tartalmazza
*/
void new_list_node(Linked_List *linked_list, Vertex_Data *node_data) {
    List_Node *list_node = alloc_list_node();
    node_data->list_node = list_node;
    list_node->node_data = node_data;
    list_node->next_node = NULL;

    if (linked_list->head_node == NULL) {
        linked_list->head_node = list_node;
        list_node->prev_node = NULL;
    } else {
        List_Node *last_node = get_last_node(linked_list);
        last_node->next_node = list_node;
        list_node->prev_node = last_node;
    }
}

// csak foglalja a memóriát, nem szabadítja fel!
Linked_List *alloc_linked_list() {
    return (Linked_List *) malloc(sizeof(Linked_List));
}

int get_vertex_data_int(Vertex_Data *vertex_data) {
    return vertex_data->id;
}

/*
    1. lista bejárása és az összes node felszabadítása
    2. lista mutató = NULL
*/
void free_linked_list(Linked_List *linked_list) {
    printf("%s:\n", __func__);
    List_Node *p = linked_list->head_node;
    List_Node *next_node = NULL;

    while (p != NULL && p->next_node != NULL) {
        next_node = p->next_node;
        printf("p = %d (%p), next_node = %d (%p)\n", get_vertex_data_int(p->node_data), p, get_vertex_data_int(next_node->node_data), next_node);
        free_list_node(p);
        p = next_node;
    }        

    if (next_node != NULL) {
        printf("p = %d (%p), next_node = %d (%p)\n", get_vertex_data_int(p->node_data), p, get_vertex_data_int(next_node->node_data), next_node);
        free_list_node(next_node);
    }

    free(linked_list);
    linked_list = NULL;
}

/*
    létrehoz egy új Linked_List-et üresen

    csak foglalja a memóriát!
*/
Linked_List *new_linked_list() {
    Linked_List *linked_list = alloc_linked_list();
    
    linked_list->head_node = NULL;

    return linked_list;
}

/*
    1.  indulás: linked_list->head_node
    2.  amíg search->next_node != NULL
            search = search->next_node
    3.  visszaadja search
*/
List_Node *get_last_node(Linked_List *linked_list) {
    List_Node *search = linked_list->head_node;

    while (search != NULL && search->next_node != NULL) {
        search = search->next_node;
    }

    return search;
}

/*
    1. last_node megkeres
    2. last_node->next_node = list_node
    3. new_node->prev_node = last_node
    4. new_node->next_node = NULL
*/
void append_list_node(Linked_List *linked_list, List_Node *list_node) {
    List_Node *last_node = get_last_node(linked_list);

    last_node->next_node = list_node;
    list_node->prev_node = last_node;
    list_node->next_node = NULL;
}

/*
    1. list_node->prev_node->next_node = list_node->next_node
    2. free_node(list_node)

    felszabadítja a memóriát!
*/
void delete_list_node(Linked_List *linked_list, List_Node *list_node) {
    printf("%s:\n", __func__);
    printf("prev_node: %d -> new_next_node: %d, deleted_node: %d\n", get_vertex_data_int(list_node->prev_node->node_data), get_vertex_data_int(list_node->next_node->node_data), get_vertex_data_int(list_node->node_data));

    if (list_node->prev_node != NULL) {
        list_node->prev_node->next_node = list_node->next_node;
    } else {
        list_node->next_node->prev_node = NULL;
        linked_list->head_node = list_node->next_node;
    }
    
    free_list_node(list_node);
}

List_Node *get_list_node(Linked_List *linked_list, Vertex_Data *vertex_data) {
    printf("%s:\n", __func__);
    List_Node *search = linked_list->head_node;

    while (search != NULL && search->node_data != vertex_data) {
        printf("search = %d (%p)\n", get_vertex_data_int(search->node_data), search);
        search = search->next_node;
    }
    
    return search;
}

/*
    bejárja a listát és kiírja az összes elemét
*/
void print_linked_list(Linked_List *linked_list) {
    List_Node *p = linked_list->head_node;
    
    printf("%s:\n", __func__);

    while (p != NULL) {
        printf("%d -> ", get_vertex_data_int(p->node_data));
        p = p->next_node;
    }

    printf("NULL\n");
}