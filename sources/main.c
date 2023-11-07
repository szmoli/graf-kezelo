#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "debugmalloc.h"

#include "constants.h"
#include "globals.h"
#include "data_types.h"
#include "linked_list.h"
#include "dynamic_array.h"

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <globals.h>

unsigned int id = 0;
Dynamic_Array *adjacency_array;

int main(int argc, char **argv) {
    //bool quit = true; // while loop kilepes
    
    SDL_Window *window = SDL_CreateWindow("NHF", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    if (window == NULL) {
        printf("no window\n");
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("no renderer\n");
        return -1;
    }
        
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if (window_surface == NULL) {
        printf("no window surface\n");
        return -1;
    }

    // testing

    adjacency_array = new_dynamic_array();

    // int hnd = 12;
    // List_Node *hn = new_list_node(&hnd, sizeof(int));
    // Linked_List *ll1 = new_linked_list();
    
    // if (ll1 == NULL) printf("ll1 nem sikerult");
    
    // Linked_List *ll2 = new_linked_list();

    // if (ll2 == NULL) printf("ll2 nem sikerult");

    array_push(adjacency_array, new_list_with_head());
    array_push(adjacency_array, new_list_with_head());
    printf("array size: %d\n", adjacency_array->size);

    print_dynamic_array(adjacency_array);
    printf("array print\n\n");

    // Vertex_Data *data1 = new_vertex_data(10, 100, 100);
    // Vertex_Data *data2 = new_vertex_data(10, 200, 100);
    // printf("vertex datak kesz\n");
    // Vertex_Data *data3 = new_vertex_data(10, 100, 100);
    // Vertex_Data *data4 = new_vertex_data(10, 100, 100);
    // Vertex_Data *data5 = new_vertex_data(10, 100, 100);
    // Vertex_Data *data6 = new_vertex_data(6);

    // Linked_List *ll1 = new_list_with_head();
    // Linked_List *ll2 = new_list_with_head();
    // print_linked_list(ll1);
    // print_linked_list(ll2);
    Linked_List *ll0 = adjacency_array->array[0];
    Linked_List *ll1 = adjacency_array->array[1];
    printf("linked lists\n\n");

    create_edge(ll0->head_node, ll1->head_node);
    print_dynamic_array(adjacency_array);
    printf("create edge\n\n");

    // new_list_node(ll1);
    // list_push(ll0, copy_list_node(ll1->head_node->next_node->next_node));
    // print_dynamic_array(adjacency_array);
    // printf("new list node\n\n");

    // list_pop(ll0, ll0->head_node->next_node->next_node);
    // print_dynamic_array(adjacency_array);
    // printf("pop\n\n");

    // print_linked_list(ll1);
    // print_linked_list(ll2);
    // list_push(ll1, ll2->head_node);
    // list_push(ll2, ll1->head_node);
    // print_linked_list(ll1);
    // print_linked_list(ll2);

    //print_linked_list(ll);
    //destroy_vertex(ll1->head_node);
    // print_dynamic_array(adjacency_array);
    // printf("destroy vertex\n\n");

    // print_linked_list(ll1);
    // print_linked_list(ll2);
    // printf("cat\n");

    // new_list_node(ll1);
    // new_list_node(ll1);
    // new_list_node(ll1);
    // new_list_node(ll2);
    // new_list_node(ll2);

    // new_list_node(ll, data5);
    // new_list_node(ll, data6);

    //print_dynamic_array(arr);
    
    // printf("debug\n");

    //print_dynamic_array(arr);
    // delete_list_node(ll, data3->list_node);
    // delete_list_node(ll, data1->list_node);
    // // delete_list_node(data4->list_node);

    // //append_list_node(ll, node1);
    // //append_list_node(ll, node2);
    // print_linked_list(ll);
    
    // // free_list_node(hn);
    printf("destroy dynamic array start\n");
    destroy_dynamic_array(adjacency_array);
    printf("destroy dynamic array\n\n");
    // printf("aaaaaaaaaaaaaaa\n");




    // testing end

    // while (!quit) {
    //     SDL_Event event;
    //     SDL_PollEvent(&event);
    // }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindowSurface(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}