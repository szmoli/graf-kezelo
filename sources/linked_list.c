#include "globals.h"
#include "data_types.h"
#include "linked_list.h"

// extern Dynamic_Array *adjacency_array;

void destroy_vertex_data(Vertex_Data *vertex_data) {
    free(vertex_data);
    vertex_data = NULL;
}

/*
    létrehoz egy új vertex_data-t a megadott paraméterek alapján

    csak memóriát foglal!
*/
Vertex_Data *new_vertex_data(unsigned int radius, int x, int y) {
    Vertex_Data *vertex_data = (Vertex_Data *) malloc(sizeof(Vertex_Data));

    vertex_data->id = id++;
    vertex_data->radius = radius;
    vertex_data->x = x;
    vertex_data->y = y;

    return vertex_data;
}

Vertex_Data *init_vertex_data() {
    Vertex_Data *vertex_data = (Vertex_Data *) malloc(sizeof(Vertex_Data));

    vertex_data->id = id++;
    vertex_data->radius = 0;
    vertex_data->x = 0;
    vertex_data->y = 0;

    return vertex_data;
}

Linked_List *get_linked_list(List_Node *list_node) {
    size_t i = 0;

    while (i < adjacency_array->size && adjacency_array->array[i]->head_node->vertex_data != list_node->vertex_data) {
        i++;
    }

    return adjacency_array->array[i];

    // for (i; i < adjacency_array->size; i++) {
    //     printf("get_ll: %d, %d\n", list_node->vertex_data->id, adjacency_array->array[i]->head_node->vertex_data->id);

    //     if (adjacency_array->array[i]->head_node->vertex_data == list_node->vertex_data) {
    //         printf("get_ll: talalt\n\n");
    //         ll = adjacency_array->array[i];
    //         break;
    //     }        
    // }

    // printf("fasz\n\n");
    // return ll;
}

/*
    pont törlése:
        1. megkeresi a nodeot az összes listában és eltávolítja belőlük
            1. végigmegy a saját listáján az összes szomszédos pontját hozzáadja egy queue-hoz
            2. végigmegy a queuen és az összes szomszédos pontjának a listájából poppolja magát majd eltávolítja a queueból
        2. array_pop() a saját indexére
        3. saját linked listjét felszabadítja, de a többi pontét nem!        

    felszabadítja a memóriát
*/
void destroy_vertex(List_Node *list_node) {
    printf("%s:\n", __func__);

    Vertex_Data *vd = list_node->vertex_data;
    Linked_List *queue = new_list_empty(); // FIFO
    Linked_List *ll = get_linked_list(list_node);

    // print_linked_list(queue);

    List_Node *p = ll->head_node;
    List_Node *prev = NULL;

    printf("start\n\n");

    while (p != NULL) {
        printf("p: %d, prev: %d\n", p->vertex_data->id, prev != NULL ? prev->vertex_data->id : -1);
        prev = p;

        if (p->vertex_data != list_node->vertex_data) {
            list_push(queue, copy_list_node(p));
        }

        list_pop(ll, p);

        p = p->next_node;
        // free(prev->vertex_data);
        // free(prev);
    }

    // free(ll);

    print_linked_list(queue);
    printf("printed queue\n\n");

    p = queue->head_node;
    prev = NULL;

    while (queue->head_node != NULL) { // queue bejárás
        prev = p;
        
        Linked_List *llp = get_linked_list(p);
        printf("queue bejaras: %d\n", p != NULL ? p->vertex_data->id : -1);
        List_Node *p2 = llp->head_node;
        List_Node *prev2 = NULL;


        while (p2 != NULL && p2->vertex_data != vd) { // queue eleméhez tartozó linked list bejárása
            prev2 = p2;
            p2 = p2->next_node;
        }
        
        // pop és free
        if (prev2 == NULL && p2 != NULL) { // első elem
            llp->head_node = p2->next_node;
            destroy_list_node(p2);
        } else if (prev2 != NULL && p2 != NULL) { // általános elem
            prev2->next_node = p2->next_node;
            destroy_list_node(p2);
        }
        
        p = p->next_node;
        list_pop(queue, prev);
        printf("queue pop\n\n");
        destroy_list_node(prev);
    }
    
    destroy_linked_list(queue);

    p = ll->head_node;
    prev = NULL;

    while (p != NULL) {
        prev = p;
        p = p->next_node;
        free(prev);
    }

    destroy_list_node(p);
    
    // if (list_node != NULL) {
    //     destroy_vertex_data(list_node->vertex_data);
    // }    

    // free(list_node);
    // list_node = NULL;

    //destroy_linked_list(queue);
}

void destroy_list_node(List_Node *list_node) {
    destroy_vertex_data(list_node->vertex_data);
    free(list_node);
    list_node = NULL;
}

void create_edge(List_Node *a, List_Node *b) {
    Linked_List *list_a = get_linked_list(a);
    Linked_List *list_b = get_linked_list(b);
    printf("got linked lists\n\n");

    list_push(list_a, copy_list_node(b));
    list_push(list_b, copy_list_node(a));
}

int get_vertex_data_int(Vertex_Data *vertex_data) {
    return vertex_data->id;
}

/*
    létrehoz egy új node-ot ami a megadott adatott tartalmazza
*/
void new_list_node(Linked_List *linked_list) {
    List_Node *list_node = (List_Node *) malloc(sizeof(List_Node));
    // node_data->list_node = list_node;
    list_node->vertex_data = init_vertex_data();

    // if (linked_list->head_node == NULL) {
    //     linked_list->head_node = list_node;
    //     list_node->prev_node = NULL;
    // } else {
    //     List_Node *last_node = get_last_node(linked_list);
    //     last_node->next_node = list_node;
    //     list_node->prev_node = last_node;
    // }

    // list_node->next_node = NULL;

    list_push(linked_list, list_node);
}

List_Node *copy_list_node(List_Node *list_node) {
    List_Node *new_list_node = (List_Node *) malloc(sizeof(List_Node));

    new_list_node->vertex_data = list_node->vertex_data;

    return new_list_node;
}

void list_push(Linked_List *linked_list, List_Node *list_node) {
    if (linked_list->head_node == NULL) {
        linked_list->head_node = list_node;
    } else {
        linked_list->tail_node->next_node = list_node;
    }

    list_node->next_node = NULL;
    linked_list->tail_node = list_node;
}

/*
    1. lista bejárása és az összes node felszabadítása
    2. lista mutató = NULL
*/
void destroy_linked_list(Linked_List *linked_list) {
    printf("%s:\n", __func__);
    List_Node *p = linked_list->head_node;
    List_Node *next_node = NULL;
    //printf("p = %d (%p), next_node = (%p)\n", p->vertex_data->id, p, next_node);

    if (p != NULL) {
        while (p->next_node != NULL) {
            next_node = p->next_node;
            //printf("p = %d (%p), next_node = %d (%p)\n", get_vertex_data_int(p->vertex_data), p, get_vertex_data_int(next_node->vertex_data), next_node);
            destroy_list_node(p);
            p = next_node;
        }
    }
    
    //printf("p = %d (%p), next_node = (%p)\n", get_vertex_data_int(p->vertex_data), p, next_node);

    free(linked_list);
    linked_list = NULL;
}

/*
    létrehoz egy új Linked_List-et egy egyedi head node-al.

    csak foglalja a memóriát!
*/
Linked_List *new_list_with_head() {
    Linked_List *linked_list = new_list_empty();

    if (linked_list == NULL) return NULL;

    new_list_node(linked_list);

    return linked_list;
}

/*
    létrehoz egy új Linked_List-et üresen

    csak foglalja a memóriát!
*/
Linked_List *new_list_empty() {
    Linked_List *linked_list = (Linked_List *) malloc(sizeof(Linked_List));

    if (linked_list == NULL) return NULL;
    
    linked_list->head_node = NULL;
    linked_list->tail_node = NULL;

    return linked_list;
}

/*
    eltávolítja a listából a lista elemet, de nem szabadítja fel, arra külön meg kell hívni a destroy_list_node()-ot
*/
void list_pop(Linked_List *linked_list, List_Node *list_node) {
    // printf("%s:\n", __func__);
    // printf("prev_node: %d -> new_next_node: %d, deleted_node: %d\n", get_vertex_data_int(list_node->prev_node->node_data), get_vertex_data_int(list_node->next_node->node_data), get_vertex_data_int(list_node->node_data));
    List_Node *prev = NULL;
    List_Node *p = linked_list->head_node;

    while (p != NULL && p->vertex_data != list_node->vertex_data) {
        printf("%d\n", p->vertex_data->id);
        prev = p;
        p = p->next_node;
    }
    
    if (prev == NULL && p != NULL) {
        printf("head pop\n\n");
        linked_list->head_node = p->next_node;
    } else if (prev != NULL && p != NULL) {
        prev->next_node = p->next_node;
        printf("standard pop\n\n");
    }

    // if (list_node == linked_list->head_node) {
    //     linked_list->head_node = list_node->next_node;
    // } else {


    //     // if (list_node->next_node != NULL) list_node->next_node->prev_node = NULL;
    //     // linked_list->head_node = list_node->next_node;
    // }
}

/*
    ID alapján visszaad egy node-ot
*/
List_Node *get_list_node(Linked_List *linked_list, unsigned int id) {
    // printf("%s:\n", __func__);
    List_Node *search = linked_list->head_node;

    while (search != NULL && search->vertex_data->id != id) {
        // printf("search = %d (%p)\n", get_vertex_data_int(search->node_data), search);
        search = search->next_node;
    }
    
    return search;
}

/*
    bejárja a listát és kiírja az összes elemét
*/
void print_linked_list(Linked_List *linked_list) {
    List_Node *p = linked_list->head_node;

    //printf("%p\n", linked_list->head_node);
    
    //printf("%s:\n", __func__);

    while (p != NULL) {
        //printf("current p: %p, next p: %p\n", p, p->next_node);
        printf("%d -> ", p->vertex_data->id);
        p = p->next_node;
    }

    printf("NULL\n");
}