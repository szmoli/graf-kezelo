#include "constants.h"
#include "debugmalloc.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "lists.h"

#include <stdbool.h>
#include <memory.h>
#include <math.h>

/**
 * @brief Bekonfigurálja az SDL-t a megadott változókra.
 * 
 * @param window Ablak változó.
 * @param window_surface Ablak felület változó.
 * @param renderer Renderer változó
 * @return true Ha sikeres a konfigurálás.
 * @return false Ha sikertelen a konfigurálás.
 */
bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_EVERYTHING);

    *window = SDL_CreateWindow("Gráfkezelő", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (*window == NULL) {
        fprintf(stderr, "%s: no window\n", __func__);
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*renderer == NULL) {
        SDL_DestroyRenderer(*renderer);
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
    }

    if (*renderer == NULL) {
        fprintf(stderr, "%s: no renderer\n", __func__);
        return false;
    }

    *window_surface = SDL_GetWindowSurface(*window);

    if (*window_surface == NULL) {
        fprintf(stderr, "%s: no window surface\n", __func__);
        return false;        
    }

    return true;
}

/**
 * @brief Leállítja az SDL ablakot és a főciklus változóját false-ra állítja.
 * 
 * @param window Ablak változó.
 * @param renderer Renderer változó.
 * @param loop A főciklus bentmaradás feltételének változója.
 */
void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop) {
    *loop = false;
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindowSurface(*window);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

/**
 * @brief Egy homogén koordinátát SDL-szerű koordinátává alakít.
 * 
 * @param point Pont, aminek a koordinátáit átalakítja
 * @param window_surface Ablak felszín
 */
void transfrom_point(Point *point, SDL_Surface *window_surface) {
    int half_x = window_surface->w / 2;
    int half_y = window_surface->h / 2;    
    point->x += half_x;
    point->y += half_y;
}

/**
 * @brief Visszaadja az ablak szélességét vagy magasságát attól függően, hogy melyik a nagyobb.
 * 
 * @param window_surface Ablakfelület változó
 * @return int A nagyobb érték
 */
int get_max_size(SDL_Surface *window_surface) {
    return window_surface->h > window_surface->w ? window_surface->w : window_surface->h;
}

void create_vertex(Vertex_List *vertices, size_t vertex_id) {
    Vertex_Node *vertex_node = new_vertex_node();
    vertex_node->vertex_data.id = vertex_id;
    vertex_node->vertex_data.selected = false;
    vertex_list_push(vertices, vertex_node);
}

/**
 * @brief Beállítja a pontoknak a koordinátáit attól függően, hogy hány pont létezik.
 * 
 * @param vertices Pontok listája
 * @param window_surface Ablak felszín
 */
void set_vertices_coords(Vertex_List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offset, int y_offset) {
    double degree = (2 * PI) / vertices->size;
    size_t degree_multiplier = 1;
    Vertex_Node *iterator = vertices->head;

    while (iterator != NULL) {
        double double_x = cos(degree * degree_multiplier) * (max_size * MAIN_CIRCLE_RADIUS_MULTIPLIER * zoom_multiplier) + x_offset;
        double double_y = sin(degree * degree_multiplier) * (max_size * MAIN_CIRCLE_RADIUS_MULTIPLIER * zoom_multiplier) + y_offset;
        // printf("coords: %lf %lf\n", double_x, double_y);
        int x = (int) double_x;
        int y = (int) double_y;
        iterator->vertex_data.center.x = x;
        iterator->vertex_data.center.y = y;

        transfrom_point(&(iterator->vertex_data.center), window_surface);
        // printf("new coord: %d %d\n", iterator->vertex_data.center.x, iterator->vertex_data.center.y);

        degree_multiplier++;
        iterator = iterator->next_node;
    }
}

int get_radius(int max_size, double mode_multiplier, double zoom_multiplier) {
    return (int) (max_size * mode_multiplier * zoom_multiplier);
}

/**
 * @brief Megrajzolja a gráfpontokat. Hasonló a draw_main_circle() függvényhez.
 * 
 * @param vertices A pontokat tartalmazó lista
 * @see draw_main_circle
 */
void draw_vertices(Vertex_List *vertices, SDL_Renderer *renderer, int radius) {
    // int size = get_max_size(window_surface);
    Vertex_Node *iterator = vertices->head;
    // int radius = (int) (size * VERTEX_CIRCLE_RADIUS_MULTIPLIER);

    while (iterator != NULL) {
        Point center = iterator->vertex_data.center;
        bool selected = iterator->vertex_data.selected;
        selected ? filledCircleRGBA(renderer, center.x, center.y, radius, SELECTED_R, SELECTED_G, SELECTED_B, SELECTED_ALPHA) : filledCircleRGBA(renderer, center.x, center.y, radius, VERTEX_R, VERTEX_G, VERTEX_B, VERTEX_ALPHA);

        printf("%d: %d %d, %d\n", iterator->vertex_data.id, iterator->vertex_data.center.x, iterator->vertex_data.center.y, radius);
        printf("%p, %p\n", iterator, iterator->next_node);
        
        iterator = iterator->next_node;
    }

    // printf("end\n");
}

int main(void) {
    SDL_Window *window = NULL;
    SDL_Surface *window_surface = NULL;
    SDL_Renderer *renderer = NULL;

    if (!config_sdl(&window, &window_surface, &renderer)) {
        fprintf(stderr, "SDL config failed\n");
        return 0;
    }

    size_t vertex_id = 0;
    double zoom_multiplier = 1;
    int x_offset = 0;
    int y_offset = 0;
    int max_size = get_max_size(window_surface);
    bool running = true;
    Vertex_List *vertices = new_vertex_list();
    Vertex_Pointer_List *selection = new_vertex_pointer_list();
    Edge_List *edges = new_edge_list();

    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
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
                    case SDLK_v:
                        create_vertex(vertices, vertex_id);
                        vertex_id++;
                        set_vertices_coords(vertices, window_surface, max_size, zoom_multiplier, x_offset, y_offset);
                        print_vertex_list(vertices);
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
                draw_vertices(vertices, renderer, get_radius(max_size, VERTEX_CIRCLE_RADIUS_MULTIPLIER, 1));
                SDL_RenderPresent(renderer);
                break;
        }
    }    

    destroy_edge_list(edges);
    destroy_vertex_pointer_list(selection);
    destroy_vertex_list(vertices);

    return 0;
}