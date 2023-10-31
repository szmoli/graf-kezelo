#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "debugmalloc.h"

#include "constants.h"
#include "linked_list.h"
#include "dynamic_array.h"

#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

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

    Dynamic_Array *arr = new_dynamic_array();

    // int hnd = 12;
    // List_Node *hn = new_list_node(&hnd, sizeof(int));
    Linked_List *ll1 = new_linked_list();
    Linked_List *ll2 = new_linked_list();
    // Vertex_Data *data1 = new_vertex_data(1);
    // Vertex_Data *data2 = new_vertex_data(2);
    // Vertex_Data *data3 = new_vertex_data(3);
    // Vertex_Data *data4 = new_vertex_data(4);
    // Vertex_Data *data5 = new_vertex_data(5);
    // Vertex_Data *data6 = new_vertex_data(6);


    // new_list_node(ll1, data1);
    // new_list_node(ll2, data2);


    // new_list_node(ll, data2);
    // new_list_node(ll, data3);
    // new_list_node(ll, data4);
    // new_list_node(ll, data5);
    // new_list_node(ll, data6);
    //print_dynamic_array(arr);


    array_push(arr, ll1);
    array_push(arr, ll2);


    //print_dynamic_array(arr);
    // // TODO: nem mukodik
    // delete_list_node(ll, data3->list_node);
    // delete_list_node(ll, data1->list_node);
    // // delete_list_node(data4->list_node);

    // //append_list_node(ll, node1);
    // //append_list_node(ll, node2);
    // print_linked_list(ll);
    
    // // free_list_node(hn);
    destroy_dynamic_array(arr);




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