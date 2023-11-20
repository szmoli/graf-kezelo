#include "constants.h"
#include "debugmalloc.h"
#include "lists.h"
#include "graphics.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#include <stdbool.h>
#include <memory.h>

/**
 * @brief Létrehoz egy gráf élt
 * 
 * @param edges Létező élek listája
 * @param to Vertex_Node amibe megy az él
 * @param from Vertex_Node amiből megy az él
 * @param directed Irányított él-e?
 */
void create_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, bool directed) {
    Edge_Node *edge_node = new_edge_node();
    edge_node->edge.directed = directed;
    edge_node->edge.to = to;
    edge_node->edge.from = from;
    edge_list_push(edges, edge_node);
}

/**
 * @brief Kirajzolja a gráf éleit
 * @todo Directed rajzolás
 * 
 * @param edges Létező élek listája
 * @param renderer SDL_Renderer
 */
void draw_edges(Edge_List *edges, SDL_Renderer *renderer) {
    Edge_Node *iterator = edges->head;

    while (iterator != NULL) {
        Point center_to = iterator->edge.to->vertex_data.center;
        Point center_from = iterator->edge.from->vertex_data.center;

        int x_to = center_to.x;
        int y_to = center_to.y;
        int x_from = center_from.x;
        int y_from = center_from.y;

        thickLineRGBA(renderer, x_to, y_to, x_from, y_from, EDGE_W, EDGE_R, EDGE_G, EDGE_B, EDGE_ALPHA);

        iterator = iterator->next_node;
    }
}

bool has_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, bool directed) {
    Edge_Node *iterator = edges->head;
    Edge_Node *previous = NULL;

    switch (directed) {
    case true:
        while (iterator != NULL) {
            previous = iterator;
            iterator = iterator->next_node;

            if (iterator->edge.to == to && iterator->edge.from == from) {
                return true;
            }
        }

        return false;
        break;
    
    case false:
        while (iterator != NULL) {
            previous = iterator;
            iterator = iterator->next_node;

            // if (((previous->edge.to == to) && (previous->edge.from == from)) || ((previous->edge.from == to) && (previous->edge.from == to))) {
            //     return true;
            // }

            if (((previous->edge.to == to) && (previous->edge.from == from)) || ((previous->edge.to == from) && (previous->edge.from == to))) {
                return true;
            }
        }

        return false;
        break;
    }
}

void delete_all_edges(Edge_List *edges, Vertex_Node *vertex_node) {
    Edge_Node *iterator = edges->head;
    Edge_Node *previous = NULL;

    while (iterator != NULL) {
        previous = iterator;
        iterator = iterator->next_node;

        if (iterator->edge.to == vertex_node || iterator->edge.from == vertex_node) {
            edge_list_pop(edges, previous);
        }
    }
}

void print_edge_node(Edge_Node *node) {
    printf("%d (%p)%s%d (%p)%s", node->edge.from->vertex_data.id, node->edge.from, node->edge.directed ? " -> " : " <-> ", node->edge.to->vertex_data.id, node->edge.from, "\n");
}

/**
 * @brief 
 * @bug Ha három pont közt van húzva két él, akkor kitöröl két élt is egy helyett
 * 
 * @param edges 
 * @param to 
 * @param from 
 * @param directed 
 */
void delete_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, bool directed) {
    Edge_Node *iterator = edges->head;
    Edge_Node *previous = NULL;
    // Edge_List *queue = new_edge_list();

    switch (directed) {
    case true:
        while (iterator != NULL) {
            previous = iterator;
            iterator = iterator->next_node;

            if (iterator->edge.to == to && iterator->edge.from == from) {
                edge_list_pop(edges, previous);
            }
        }
        break;
    
    case false:
        while (iterator != NULL && (!(iterator->edge.to == to && iterator->edge.from == from) && !(iterator->edge.from == to && iterator->edge.from == to))) {
            // previous = iterator;

            // if ((iterator->edge.to == to && iterator->edge.from == from) || (iterator->edge.from == to && iterator->edge.from == to)) {
            //     // edge_list_pop(edges, previous);
            //     // edge_list_push(queue, iterator);
            // }
            
            iterator = iterator->next_node;
        }
        break;
    }

    printf("[delete edge] iterator:\n");
    //print_edge_node(iterator);
    printf("%p\n", iterator);
    edge_list_pop(edges, iterator);
    // printf("[delete edge] edge list:\n");
    // print_edge_list(queue);
    // printf("[delete edge] edge list vege\n");

    // iterator = queue->head;

    // while (iterator != NULL) {
    //     printf
    //     printf("[delete edge] popped\n");
    //     iterator = iterator->next_node;
    // }

    // destroy_edge_list(queue);
}

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

    size_t vertex_id = 0;
    double zoom_multiplier = 1;
    int x_offset = 0;
    int y_offset = 0;
    int max_size = get_max_size(window_surface);
    bool running = true;
    Vertex_List *vertices = new_vertex_list();
    Vertex_Pointer_List *selection = new_vertex_pointer_list();
    Edge_List *edges = new_edge_list();

    printf("program config kesz\n\n");

    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    window_surface = SDL_GetWindowSurface(window);
                    max_size = get_max_size(window_surface);
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                    break;

                default:
                    break;
                }
                
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        Vertex_Node *clicked_node = get_clicked_node(&event, vertices);

                        if (clicked_node == NULL) { // kijelölés törlése
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

                            printf("kijelolve: %p\n", clicked_node);

                            printf("selection:\n");
                            print_vertex_pointer_list(selection);
                            printf("select vege\n");
                        } else if (clicked_node->vertex_data.selected) { // kijelölés megszüntetése
                            unselect_vertex(selection, get_vertex_pointer_node(selection, clicked_node));
                            //! @bug selection tail nem nullazodik ki
                            printf("selection:\n");
                            print_vertex_pointer_list(selection);
                            printf("\n");
                        }
                        break;
                    default:
                        break;
                }

                break;

            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) { // up
                    zoom_multiplier += ZOOM_STEP;
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                } else if (event.wheel.y < 0 && zoom_multiplier - ZOOM_STEP > 0) { // down
                    zoom_multiplier -= ZOOM_STEP;
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                }

                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_e: // él létrehozás
                        switch (selection->size) {
                        case 2:
                            Vertex_Node *from = selection->head->vertex_node;
                            Vertex_Node *to = selection->head->next_node->vertex_node;

                            if (!has_edge(edges, to, from, false)) {
                                create_edge(edges, to, from, false);
                                printf("edges: ");
                                print_edge_list(edges);
                                printf("\n");
                            } else {
                                printf("%d <-> %d\n\n", from->vertex_data.id, to->vertex_data.id);
                            }
                            break;

                        default:
                            printf("nem megfelelo szamu pont kijelolve\n\n");
                            break;
                        }
                        break;

                    case SDLK_d: // él törlése
                        switch (selection->size) {
                        case 2:
                            Vertex_Node *from = selection->head->vertex_node;
                            Vertex_Node *to = selection->head->next_node->vertex_node;
                            delete_edge(edges, to, from, false);
                            printf("edges:\n");
                            print_edge_list(edges);
                            printf("\n");
                            break;

                        default:
                            printf("nem megfelelo szamu pont kijelolve\n\n");
                            break;
                        }
                        break;

                    case SDLK_a: // minden él törlése
                        switch (selection->size) {
                        case 1:
                            delete_all_edges(edges, selection->head->vertex_node);
                            printf("edges:\n");
                            print_edge_list(edges);
                            printf("\n");
                            break;

                        default:
                            printf("nem megfelelo szamu pont kijelolve\n\n");
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
                SDL_SetRenderDrawColor(renderer, BG_R, BG_G, BG_B, BG_ALPHA);
                SDL_RenderClear(renderer);
                draw_edges(edges, renderer);
                draw_vertices(vertices, renderer);
                SDL_RenderPresent(renderer);
                break;
        }
    }    

    destroy_edge_list(edges);
    destroy_vertex_pointer_list(selection);
    destroy_vertex_list(vertices);

    printf("program vege\n");

    return 0;
}