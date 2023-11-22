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
 * @todo Megcsinálni az irányított éleket
 * 
 * @param edges Létező élek listája
 * @param to Melyik pontból
 * @param from Melyik pontba
 * @param directed Irányított él-e?
 */
void create_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, bool directed) {
    Edge_Node *edge_node = new_edge_node();
    edge_node->edge.to = to;
    edge_node->edge.from = from;
    edge_node->edge.directed = false;
    edge_node->edge.red = EDGE_R;
    edge_node->edge.green = EDGE_G;
    edge_node->edge.blue = EDGE_B;
    edge_node->edge.alpha = EDGE_ALPHA;
    edge_node->edge.width = EDGE_W;
    edge_list_push(edges, edge_node);
}

/**
 * @brief Kirajzolja az éleket
 * @todo Irányított élek kirajzolása
 * 
 * @param edges Létező élek listája
 * @param renderer SDL_Renderer
 */
void draw_edges(Edge_List *edges, SDL_Renderer *renderer) {
    Edge_Node *iterator = edges->head;

    while (iterator != NULL) {
        Point center_to = iterator->edge.to->vertex_data.center;
        Point center_from = iterator->edge.from->vertex_data.center;
        Edge edge = iterator->edge;

        int x_to = center_to.x;
        int y_to = center_to.y;
        int x_from = center_from.x;
        int y_from = center_from.y;

        thickLineRGBA(renderer, x_to, y_to, x_from, y_from, edge.width, edge.red, edge.green, edge.blue, edge.alpha);

        iterator = iterator->next_node;
    }
}

/**
 * @brief Megkeresi a két pont közt húzott élt
 * 
 * @param edges Létező élek listája
 * @param to Melyik pontból
 * @param from Melyik pontba
 * @return Edge_Node* NULL, ha nincs köztük él
 */
Edge_Node *get_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from) {
    Edge_Node *iterator = edges->head;

    while (iterator != NULL && !((iterator->edge.from == from) && (iterator->edge.to == to))) iterator = iterator->next_node;

    return iterator;
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
                    case SDLK_LALT:
                        SDL_SetModState(KMOD_ALT);
                        break;

                    case SDLK_LCTRL:
                        SDL_SetModState(KMOD_CTRL);
                        break;

                    //! @bug második él csinálásnál meghal a progi
                    case SDLK_e: // él létrehozás
                        switch (selection->size) {
                        case 2:
                            Vertex_Node *from = selection->head->vertex_node;
                            Vertex_Node *to = selection->head->next_node->vertex_node;

                            if (get_edge(edges, to, from) == NULL) {
                                create_edge(edges, to, from, false);
                            } else {
                                printf("mar van el koztuk\n\n");
                            }

                            break;

                        default:
                            printf("nem megfelelo szamu pont kijelolve\n\n");
                            break;
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