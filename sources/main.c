#include "constants.h"
#include "debugmalloc.h"
#include "lists.h"
#include "graphics.h"
#include "saves.h"
#include "SDL.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(void) {
    printf("program eleje\n");

    SDL_Window *window = NULL;
    SDL_Surface *window_surface = NULL;
    SDL_Renderer *renderer = NULL;

    if (!config_sdl(&window, &window_surface, &renderer)) {
        fprintf(stderr, "SDL config failed\n");
        return 0;
    }

    printf("SDL config kesz\n");

    int vertex_id = 0;
    double zoom_multiplier = 1;
    int x_offset = 0;
    int y_offset = 0;
    int max_size = get_max_size(window_surface);
    bool running = true;
    bool render = true;
    char *date_time_str = NULL;
    Vertex_List *vertices = new_vertex_list();
    Vertex_Pointer_List *selection = new_vertex_pointer_list();
    Edge_List *edges = new_edge_list();

    printf("program config kesz\n\n");

    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_DROPFILE:
                char *file_path = event.drop.file;
                printf("file dropped: %s\n", file_path);

                if (is_valid_graph_file(event.drop.file, GRAPH_FILE_EXTENSION)) {
                    clear_vertex_list(vertices);
                    clear_vertex_pointer_list(selection);
                    clear_edge_list(edges);

                    date_time_str = get_date_time_str_from_file_path(file_path);

                    char *vertices_save_path = get_save_file_path(SAVES_DIR, VERTEX_FILE_EXTENSION, date_time_str);
                    char *edges_save_path = get_save_file_path(SAVES_DIR, EDGE_FILE_EXTENSION, date_time_str);

                    load_graph(vertices, edges, selection,  vertices_save_path, edges_save_path, &vertex_id);
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                    render = true;

                    free(vertices_save_path);
                    free(edges_save_path);
                }

                break;

            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    window_surface = SDL_GetWindowSurface(window);
                    max_size = get_max_size(window_surface);
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                    render = true;
                    break;

                default:
                    break;
                }
                
                break;
            case SDL_MOUSEBUTTONDOWN:
                render = true;

                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        Vertex_Node *clicked_node = get_clicked_node(&event, vertices);

                        if (clicked_node == NULL && selection->size != 0) { // kijelölés törlése
                            printf("clicked nothing\n");
                            printf("selection head: %p\n", selection->head);
                            printf("selection tail: %p\n", selection->tail);
                            Vertex_Pointer_Node *iterator = selection->head;
                            Vertex_Pointer_Node *previous = NULL;
                            printf("[loop elott] iterator: %p, previous: %p, iterator next: %p\n", iterator, previous, iterator == NULL ? NULL : iterator->next_node);
                            printf("selection: ");
                            print_vertex_pointer_list(selection);

                            while (iterator != NULL) {
                                printf("[loopban] iterator next: %p\n", iterator->next_node);
                                previous = iterator;
                                iterator = iterator->next_node;
                                
                                unselect_vertex(selection, previous);

                                printf("[loopban] selection: ");
                                print_vertex_pointer_list(selection);
                                printf("\n\n");
                            }
                        } else if (clicked_node != NULL && !(clicked_node->vertex_data.selected)) { // kijelölés
                            select_vertex(selection, clicked_node);

                            printf("kijelolve: %p\n\n", clicked_node);
                        } else if (clicked_node != NULL && clicked_node->vertex_data.selected) { // kijelölés megszüntetése
                            printf("clicked node: %p\n", clicked_node);
                            Vertex_Pointer_Node *vp = get_vertex_pointer_node(selection, clicked_node);
                            printf("kijeloles megszuntetve: %p\n", clicked_node);
                            printf("vertex pointer: %p\n\n", vp);
                            unselect_vertex(selection, vp);
                        }
                        break;

                    default:
                        break;
                }

                break;

            case SDL_MOUSEWHEEL:
                render = true;


                if (event.wheel.y > 0) { // up
                    zoom_multiplier += ZOOM_STEP;
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                } else if (event.wheel.y < 0 && zoom_multiplier - ZOOM_STEP > 0) { // down
                    zoom_multiplier -= ZOOM_STEP;
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                }

                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LALT:
                        SDL_SetModState(KMOD_NONE);
                        break;

                    case SDLK_LCTRL:
                        SDL_SetModState(KMOD_NONE);
                        break;

                    default:
                        break;
                }

                break;

            case SDL_KEYDOWN:
                render = true;

                switch (event.key.keysym.sym) {
                    case SDLK_s:
                        switch (SDL_GetModState()) {
                            case KMOD_CTRL:
                                check_and_make_saves_dir(SAVES_DIR);

                                if (date_time_str == NULL) {
                                    date_time_str = get_date_time_str();
                                }

                                char *vertices_save_path = get_save_file_path(SAVES_DIR, VERTEX_FILE_EXTENSION, date_time_str);
                                char *edges_save_path = get_save_file_path(SAVES_DIR, EDGE_FILE_EXTENSION, date_time_str);
                                char *graph_save_path = get_save_file_path(SAVES_DIR, GRAPH_FILE_EXTENSION, date_time_str);

                                save_graph(vertices, edges, vertices_save_path, edges_save_path, graph_save_path);

                                free(vertices_save_path);
                                free(edges_save_path);
                                free(graph_save_path);

                                break;
                            
                            default:
                                break;
                        }

                        break;

                    case SDLK_LALT:
                        SDL_SetModState(KMOD_ALT);
                        break;

                    case SDLK_LCTRL:
                        SDL_SetModState(KMOD_CTRL);
                        break;

                    case SDLK_e: // él létrehozás
                        switch (selection->size) {
                        case 2:
                            Vertex_Node *from = selection->head->vertex_node;
                            Vertex_Node *to = selection->head->next_node->vertex_node;

                            if (get_edge(edges, to, from) == NULL) {
                                create_edge(edges, to, from);
                                unselect_vertex(selection, selection->head->next_node);
                            } else {
                                printf("mar van el koztuk\n\n");
                            }

                            break;

                        default:
                            printf("nem megfelelo szamu pont kijelolve\n\n");
                            break;
                        }

                        break;

                    case SDLK_DELETE:
                        Vertex_Pointer_Node *selection_iterator = selection->head;
                        Vertex_Pointer_Node *selection_previous = NULL;

                        while (selection_iterator != NULL) {
                            selection_previous = selection_iterator;
                            selection_iterator = selection_iterator->next_node;

                            Edge_Node *edges_iterator = edges->head;
                            Edge_Node *edges_previous = NULL;

                            while (edges_iterator != NULL) {
                                edges_previous = edges_iterator;
                                edges_iterator = edges_iterator->next_node;

                                if (edges_previous->edge.to == selection_previous->vertex_node || edges_previous->edge.from == selection_previous->vertex_node) {
                                    edge_list_pop(edges, edges_previous);
                                }
                            }

                            vertex_list_pop(vertices, selection_previous->vertex_node);
                            vertex_pointer_list_pop(selection, selection_previous);
                            set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        }

                        break;

                    //! @bug ctrl + d az összes letezo edget torli XD
                    case SDLK_d: // él törlése
                        switch (SDL_GetModState()) {
                            case KMOD_NONE:
                                switch (selection->size) {
                                    case 2:
                                        Vertex_Node *from = selection->head->vertex_node;
                                        Vertex_Node *to = selection->head->next_node->vertex_node;
                                        edge_list_pop(edges, get_edge(edges, to, from));
                                        break;
                                    
                                    default:
                                        printf("nem megfelelo kijeloles\n");
                                        break;
                                }
                                
                                break;

                            case KMOD_ALT:
                                switch (selection->size) {
                                    case 1:
                                        Vertex_Node *from = selection->head->vertex_node;
                                        
                                        Edge_Node *iterator = edges->head;
                                        Edge_Node *previous = NULL;

                                        //! @bug lehet bug idk
                                        while (iterator != NULL) {
                                            previous = iterator;
                                            iterator = iterator->next_node;
                                            edge_list_pop(edges, previous);
                                        }

                                        break;
                                    
                                    default:
                                        printf("nem megfelelo kijeloles\n");
                                        break;
                                }
                                
                                break;
                            
                            default:
                                break;
                        }

                        break;

                    case SDLK_v: // vertex létrehozás
                        create_vertex(vertices, vertex_id, get_radius(max_size, VERTEX_CIRCLE_RADIUS_MULTIPLIER, 1));
                        print_vertex_list(vertices);
                        printf("vertex created\n");
                        vertex_id++;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        printf("vertex coords set\n");
                        printf("\n");
                        break;

                    case SDLK_LEFT:
                        x_offset += MOVE_STEP;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        break;

                    case SDLK_RIGHT:
                        x_offset -= MOVE_STEP;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        break;

                    case SDLK_UP:
                        y_offset += MOVE_STEP;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        break;

                    case SDLK_DOWN:
                        y_offset -= MOVE_STEP;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        break;

                    case SDLK_r: // zoom és offset reset
                        x_offset = 0;
                        y_offset = 0;
                        zoom_multiplier = 1;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        break;

                    default:
                        break;
                }

                break;

            case SDL_QUIT:
                quit_sdl(&window, &renderer, &running);
                break;

            default: // rendering
                switch (render) {
                    case true:
                        render = false;

                        SDL_SetRenderDrawColor(renderer, BG_R, BG_G, BG_B, BG_ALPHA);
                        SDL_RenderClear(renderer);
                        draw_edges(edges, renderer);
                        draw_vertices(vertices, renderer);
                        SDL_RenderPresent(renderer);

                        break;
                    
                    default:
                        break;
                }
                
                break;
        }
    }

    destroy_edge_list(edges);
    destroy_vertex_pointer_list(selection);
    destroy_vertex_list(vertices);

    printf("program vege\n");

    return 0;
}