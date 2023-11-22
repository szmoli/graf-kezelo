#include "constants.h"
#include "debugmalloc.h"
#include "lists.h"
#include "graphics.h"
#include "SDL.h"

#include <stdbool.h>
#include <memory.h>

void save_vertex_list(Vertex_List *list) {
    Vertex_Node *iterator = list->head;

    while (iterator != NULL) {
        Vertex_Data vd = iterator->vertex_data;

        // id, selected, center x, center y, red, green, blue, alpha, radius
        printf("%c,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", VERTEX_SAVE_HEADER, vd.id, vd.selected ? 1 : 0, vd.center.x, vd.center.y, VERTEX_R, VERTEX_G, VERTEX_B, VERTEX_ALPHA, vd.radius);

        iterator = iterator->next_node;
    }
}

void save_edge_list(Edge_List *list) {
    Edge_Node *iterator = list->head;

    while (iterator != NULL) {
        Edge edge = iterator->edge;
        Vertex_Data vd_to = edge.to->vertex_data;
        Vertex_Data vd_from = edge.from->vertex_data;

        // from, to, red, green, blue, alpha, width
        printf("%c,%d,%d,%d,%d,%d,%d,%d,%d\n", EDGE_SAVE_HEADER, vd_from.id, vd_to.id, EDGE_R, EDGE_G, EDGE_B, EDGE_ALPHA, EDGE_W);

        iterator = iterator->next_node;
    }
}

void save_vertex_pointer_list(Vertex_Pointer_List *list) {
    Vertex_Pointer_Node *iterator = list->head;

    while (iterator != NULL) {
        Vertex_Data vd = iterator->vertex_node->vertex_data;
        printf("%c,%d\n", SELECTION_SAVE_HEADER, vd.id);
        iterator = iterator->next_node;
    }    
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

                            printf("kijelolve: %d (%p)\n\n", clicked_node->vertex_data.id, clicked_node);
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
                switch (event.key.keysym.sym) {
                    case SDLK_s:
                        switch (SDL_GetModState()) {
                            case KMOD_CTRL:
                                save_vertex_list(vertices);
                                printf("\n");
                                save_edge_list(edges);
                                printf("\n");
                                save_vertex_pointer_list(selection);
                                printf("\n");
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

                    case SDLK_a: // debug
                        printf("breakpoint\n");
                        break;

                    case SDLK_e: // él létrehozás
                        switch (selection->size) {
                        case 2:
                            Vertex_Node *from = selection->head->vertex_node;
                            Vertex_Node *to = selection->head->next_node->vertex_node;

                            if (get_edge(edges, to, from) == NULL) {
                                create_edge(edges, to, from);
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

                    //! @bug lecrashel, mert nem nezzuk a selection sizet a deletenel: ha alt + d akkor a size 1 kell legyen, ha sima d, akkor pedig 2 kell legyen
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