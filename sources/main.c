#include "constants.h"
#include "debugmalloc.h"
#include "lists.h"
#include "graphics.h"
#include "SDL.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <Windows.h>
#include <time.h>
#include <string.h>

/**
 * @brief A hívás időpontjából csinál egy stringet
 * 
 * @return char* Idő és dátum string
 */
char *get_date_time_str() {
    time_t raw_time;
    time(&raw_time);
    struct tm *local_time = localtime(&raw_time);
    size_t buffer_size = 25;
    char *buffer = (char *) malloc((buffer_size + 1) * sizeof(char));

    while (strftime(buffer, buffer_size, "%Y-%m-%d_%H%M%S", local_time) == 0) {
        free(buffer);
        buffer_size *= 2;
        buffer = (char *) malloc((buffer_size + 1) * sizeof(char));
    }

    return buffer;
}

//! @todo create buffer with big enough size
//! @todo megcsinalni ezt a functiont vegre
/**
 * @brief 
 * 
 * @return char* Mentés fájl neve
 */
char *get_save_file_path(char *saves_dir, char *extension, char *time_str) {
    char *save_path = (char *) malloc((strlen(saves_dir) + strlen(time_str) + strlen(extension) + 1) * sizeof(char));

    strcpy(save_path, saves_dir);
    strcat(save_path, time_str);
    strcat(save_path, extension);

    return save_path;
}

/**
 * @brief Ellenőrzi, hogy van-e már a programnak mentések mappája, ha nincs akkor létrehozza
 * 
 * @param saves_dir Mappa elérési útvonala
 */
void check_and_make_saves_dir(char *saves_dir) {
    struct stat st;

    if (stat(SAVES_DIR, &st) == -1) {
        _mkdir(SAVES_DIR); 
    }
}

/**
 * @brief Elmenti a megadott listát a megadott helyre
 * 
 * @param list 
 * @param save_file 
 */
void save_vertex_list(Vertex_List *list, FILE *save_file) {
    Vertex_Node *iterator = list->head;

    while (iterator != NULL) {
        Vertex_Data vd = iterator->vertex_data;

        // id, selected, center x, center y, red, green, blue, alpha, radius
        fprintf(save_file, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", vd.id, vd.selected ? 1 : 0, vd.center.x, vd.center.y, VERTEX_R, VERTEX_G, VERTEX_B, VERTEX_ALPHA, vd.radius);

        iterator = iterator->next_node;
    }
}

/**
 * @brief Elmenti a megadott listát a megadott helyre
 * 
 * @param list 
 * @param save_file 
 */
void save_edge_list(Edge_List *list, FILE *save_file) {
    Edge_Node *iterator = list->head;

    while (iterator != NULL) {
        Edge edge = iterator->edge;
        Vertex_Data vd_to = edge.to->vertex_data;
        Vertex_Data vd_from = edge.from->vertex_data;

        // from, to, red, green, blue, alpha, width
        fprintf(save_file, "%d,%d,%d,%d,%d,%d,%d\n", vd_from.id, vd_to.id, EDGE_R, EDGE_G, EDGE_B, EDGE_ALPHA, EDGE_W);

        iterator = iterator->next_node;
    }
}

/**
 * @brief Elmenti a megadott listát a megadott helyre
 * 
 * @param list 
 * @param save_file 
 */
void save_vertex_pointer_list(Vertex_Pointer_List *list, FILE *save_file) {
    Vertex_Pointer_Node *iterator = list->head;

    while (iterator != NULL) {
        Vertex_Data vd = iterator->vertex_node->vertex_data;
        fprintf(save_file, "%d\n", vd.id);
        iterator = iterator->next_node;
    }    
}

/**
 * @brief Elmenti a teljes gráfot
 * 
 * @param vertices 
 * @param edges 
 * @param selection 
 * @param vertices_save_path 
 * @param edges_save_path 
 * @param selection_save_path 
 */
void save_graph(Vertex_List *vertices, Edge_List *edges, Vertex_Pointer_List *selection, char *vertices_save_path, char *edges_save_path, char *selection_save_path, char *graph_save_path) {
    FILE *vertices_save_file = fopen(vertices_save_path, "w");
    FILE *edges_save_file = fopen(edges_save_path, "w");
    FILE *selection_save_file = fopen(selection_save_path, "w");
    FILE *graph_save_file = fopen(graph_save_path, "w");

    save_vertex_list(vertices, vertices_save_file);
    save_edge_list(edges, edges_save_file);
    save_vertex_pointer_list(selection, selection_save_file);

    fclose(vertices_save_file);
    fclose(edges_save_file);
    fclose(selection_save_file);
    fclose(graph_save_file);
}

/**
 * @brief Ellenőtzi, hogy megfelelő fájlt kapott-e a program
 * 
 * @param file_path Fájl elérési útvonala
 * @param graph_file_estension Helyes fájlkiterjesztés
 * @return true Ha a megadott fájl kiterjesztése egyezik a helyes kiterjesztéssel
 * @return false He nem egyeznek
 */
bool is_valid_graph_file(char *file_path, char *graph_file_estension) {
    char *last = strrchr(file_path, '.');
    
    return (strcmp(last, graph_file_estension) == 0);
}

/**
 * @brief Kiveszi a dátumot és időt a megnyitott fájl elérési útvonalából
 * 
 * @param file_path Elérési útvonal
 * @return char* Dátum és idő string
 */
char *get_date_time_str_from_file_path(char *file_path) {
    char *last = strrchr(file_path, '\\');
    char *token = strtok(last + 1, ".");
    return token;
}

/**
 * @brief Betölti a gráf pontokat
 * 
 * @param vertices Gráf pontok listája
 * @param file Gráf pontok mentés fájlja
 */
void load_vertex_list(Vertex_List *vertices, FILE *file) {
    bool reading = true;
    
    while (reading) {
        Vertex_Node *node = new_vertex_node();
        Vertex_Data vd = node->vertex_data;

        if (fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", &(vd.id), &(vd.selected), &(vd.center.x), &(vd.center.y), &(vd.green), &(vd.blue), &(vd.red), &(vd.alpha), &(vd.radius)) == 9) {
            vertex_list_push(vertices, node);

        } else {
            free(node);
            reading = false;
        }
    }
}

/**
 * @brief Betölti a gráf éleket
 * 
 * @param edges Gráf élek listája
 * @param file Gráf élek mentés fájlja
 */
void load_edge_list(Edge_List *edges, FILE *file) {
    printf("%s\n", __func__);
}

/**
 * @brief Betölti a kijelöléseket
 * 
 * @param selection Kijelölések listája
 * @param file Kijelölések mentés fájlja
 */
void load_vertex_pointer_list(Vertex_Pointer_List *selection, FILE *file) {
    printf("%s\n", __func__);
}

void load_graph(Vertex_List *vertices, Edge_List *edges, Vertex_Pointer_List *selection, char *vertices_save_path, char *edges_save_path, char *selection_save_path) {
    FILE *vertices_save_file = fopen(vertices_save_path, "r");
    FILE *edges_save_file = fopen(edges_save_path, "r");
    FILE *selection_save_file = fopen(selection_save_path, "r");

    load_vertex_list(vertices, vertices_save_file);
    load_edge_list(edges, edges_save_file);
    load_vertex_pointer_list(selection, selection_save_file);
    
    fclose(vertices_save_file);
    fclose(edges_save_file);
    fclose(selection_save_file);
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
                    date_time_str = get_date_time_str_from_file_path(file_path);

                    char *vertices_save_path = get_save_file_path(SAVES_DIR, VERTEX_FILE_EXTENSION, date_time_str);
                    char *edges_save_path = get_save_file_path(SAVES_DIR, EDGE_FILE_EXTENSION, date_time_str);
                    char *selection_save_path = get_save_file_path(SAVES_DIR, SELECTION_FILE_EXTENSION, date_time_str);

                    load_graph(vertices, edges, selection, vertices_save_path, edges_save_path, selection_save_path);

                    free(vertices_save_path);
                    free(edges_save_path);
                    free(selection_save_path);

                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
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
                                char *selection_save_path = get_save_file_path(SAVES_DIR, SELECTION_FILE_EXTENSION, date_time_str);
                                char *graph_save_path = get_save_file_path(SAVES_DIR, GRAPH_FILE_EXTENSION, date_time_str);

                                save_graph(vertices, edges, selection, vertices_save_path, edges_save_path, selection_save_path, graph_save_path);

                                free(vertices_save_path);
                                free(edges_save_path);
                                free(selection_save_path);
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