/**
 * @brief Gráfkezelő program
 */

#include "constants.h"
#include "SDL2_gfxPrimitives.h"
#include "debugmalloc.h"
#include "typedefs.h"
#include "linked_list.h"
#include "dynamic_array.h"
#include "graph.h"
#include "graphics.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main(void) {
    /**
     * @brief A gráfpont azonosító.
     * @details Minden pontnak egyedi azonosítója van. Az azonosító mindig egyel növekszik, amikor egy új pontot hozunk létre, így gyakorlatilag a létrehozható pontjainknak felső határa 4294967295, azaz az unsigned int felső határa. 
     */
    unsigned int id = 0;

    /**
     * @brief Lista az összes létező gráfpontról (Vertex_Data).
     * @details Amikor egy új pontot hozunk létre, azt ebben a listában tartjuk nyilván. Ha a felhasználó kitöröl egy pontot, az a listából is törlődik. A gráfot tároló adatstruktúra ennek a listának a tárolt pontjaira mutat, ha kitörlünk egy pontot, akkor azt a gráf adatstruktúrájából is kitöröljük.
     */
    List *vertices = new_list();
    List *selected_vertices = new_list();

    /**
     * @brief Egy dinamikus tömb, ami az összes ponthoz tartozó szomszédosságokat tárolja.
     * @details Amikor egy új pontot hozunk létre, ehhez a tömbhöz hozzáadunk egy láncolt listát, aminek a legelején egy mutató van a létrehozott pontra. Ha ezt a pontot összekötjük egy másikkal, akkor mindkettőjük listájához hozzáadunk egy mutatót a másik pontra. Így tárolódnak el a szomszédosságok.
     */
    Array *neighbour_arr = new_array();

    SDL_Window *window = NULL;
    SDL_Surface *window_surface = NULL;
    SDL_Renderer *renderer = NULL;

    if (!config_sdl(&window, &window_surface, &renderer)) {
        fprintf(stderr, "%s: config failed\n\n", __func__);
        return -1;
    }

    bool running = true;
    double zoom_multiplier = 1;
    int x_offset = 0;
    int y_offset = 0;
    int max_size = get_max_size(window_surface);
#ifdef DEBUG
    Point main_circle_center = { .x = 0, .y = 0 };
    Point old_main_circle_center;
#endif

    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
    // new_vertex(neighbour_arr, vertices, new_vertex_data(&id));

    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        window_surface = SDL_GetWindowSurface(window);

                        //printf("resizing: %dx%d\n", window_surface->w, window_surface->h);
                        break;

                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                quit_sdl(&window, &renderer, &running);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_v:
                        new_vertex(neighbour_arr, vertices, new_vertex_data(&id));
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        break;
                    case SDLK_LEFT:
                        // for_each(vertices, move_vertex_center_left);
                        x_offset += MOVE_STEP;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
#ifdef DEBUG
                        main_circle_center.x += MOVE_STEP;
#endif
                        break;
                    case SDLK_RIGHT:
                        x_offset -= MOVE_STEP;
                        // for_each(vertices, move_vertex_center_right);
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
#ifdef DEBUG
                        main_circle_center.x -= MOVE_STEP;

#endif
                        break;
                    case SDLK_UP:
                        y_offset += MOVE_STEP;
                        // for_each(vertices, move_vertex_center_up);
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
#ifdef DEBUG
                        main_circle_center.y += MOVE_STEP;
#endif
                        break;
                    case SDLK_DOWN:
                        y_offset -= MOVE_STEP;
                        // for_each(vertices, move_vertex_center_down);
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
#ifdef DEBUG
                        main_circle_center.y -= MOVE_STEP;
#endif
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                Node *clicked_node = get_clicked_node(&event, vertices, get_radius(max_size, VERTEX_CIRCLE_RADIUS_MULTIPLIER, 1));

                //! @todo Befejezni a selection cuccokat.
                if (clicked_node == NULL) {
                    for_each(selected_vertices, deselect_original_node);
                    list_clear(selected_vertices, false);
                    //print_list(selected_vertices, VERTEX_DATA_POINTER);
                    //printf("cleared selected_vertices\n\n");
                } else {
                    if (!(((Vertex_Data *)clicked_node->data)->selected)) { // ha nem volt kiválasztva, akkor kiválasztjuk
                        select_node(clicked_node);
                        Node *copied_clicked_node = copy_node(clicked_node);
                        list_push(selected_vertices, copied_clicked_node);
                        print_list(selected_vertices, VERTEX_DATA_POINTER);
                    } else { // ha ki volt választva, akkor "nemkiválasztjuk"
                        deselect_node(clicked_node);
                        //! @todo Kiszedni a kijelolt listából
                    }
                }

                //print_list(selected_vertices, VERTEX_DATA_POINTER);
                //clicked_node == NULL ? printf("no collision\n") : print_node(clicked_node, VERTEX_DATA);
                // switch (expression) {
                // case /* constant-expression */:
                //     /* code */
                //     break;
                
                // default:
                //     break;
                // }
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y > 0) { // up
                    zoom_multiplier += ZOOM_STEP;
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                    //printf("zoom: %lf\n", zoom_multiplier);
                } else if (event.wheel.y < 0 && zoom_multiplier - ZOOM_STEP > 0) { // down
                    zoom_multiplier -= ZOOM_STEP;
                    set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);

                    //printf("zoom: %lf\n", zoom_multiplier);
                }
                break;
            default:
                SDL_SetRenderDrawColor(renderer, BG_R, BG_G, BG_B, BG_ALPHA);
                SDL_RenderClear(renderer);

#ifdef DEBUG
                // (&main_circle_center)->x += x_offset;
                // (&main_circle_center)->y += y_offset;
                draw_main_circle(window_surface, renderer, get_radius(max_size, MAIN_CIRCLE_RADIUS_MULTIPLIER, zoom_multiplier), main_circle_center); //! @bug
#endif

                draw_vertices(vertices, renderer, get_radius(max_size, VERTEX_CIRCLE_RADIUS_MULTIPLIER, 1));

                SDL_RenderPresent(renderer);
                break;
        }
    }

    destroy_array(neighbour_arr, LINKED_LIST, false);
    destroy_list(selected_vertices, false);
    destroy_list(vertices, true);
    printf("program vege\n");
    return 0;
}