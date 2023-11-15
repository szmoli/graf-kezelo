/**
 * @file graphics.c
 * @brief Ez a fájl a grafikus függvényeket tartalmazza.
 * 
 */

#include "graphics.h"

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

/**
 * @brief Megrajzolja a fő kört, amin az összes gráfpont elhelyezkedik.
 * 
 * @param window_surface Ablak felszín változó
 * @param renderer Renderer változó
 * @param x Középpont x koorinátája
 * @param y Középpont y koordinátája
 * @param r Piros
 * @param g Zöld
 * @param b Kék
 * @param a Alpha
 */
void draw_main_circle(SDL_Surface *window_surface, SDL_Renderer *renderer, int radius, Point center) {
    // int size = get_max_size(window_surface);

    // int radius = (int) size * MAIN_CIRCLE_RADIUS_MULTIPLIER;
    // Point center = { .x = MAIN_CIRCLE_X, .y = MAIN_CIRCLE_Y };

    transfrom_point(&center, window_surface);
    aacircleRGBA(renderer, center.x, center.y, radius, DEBUG_R, DEBUG_G, DEBUG_B, DEBUG_ALPHA); // kör
    filledCircleRGBA(renderer, center.x, center.y, radius * MAIN_CIRCLE_CENTER_RADIUS_MULTIPLIER, DEBUG_R, DEBUG_G, DEBUG_B, DEBUG_ALPHA); // középpont
}

/**
 * @brief Beállítja a pontoknak a koordinátáit attól függően, hogy hány pont létezik.
 * 
 * @param vertices Pontok listája
 * @param window_surface Ablak felszín
 */
void set_vertices_coords(List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offset, int y_offset) {
    double degree = (2 * PI) / vertices->size;
    size_t degree_multiplier = 1;
    Node *p = vertices->head_node;
    // int size = get_max_size(window_surface);

    while (p != NULL) {
        // int x = (int) (round(cos(degree * degree_multiplier))) * (round(window_surface->h * MAIN_CIRCLE_RADIUS_MULTIPLIER));
        // int y = (int) (round(sin(degree * degree_multiplier))) * (round(window_surface->h * MAIN_CIRCLE_RADIUS_MULTIPLIER));

        double double_x = cos(degree * degree_multiplier) * (max_size * MAIN_CIRCLE_RADIUS_MULTIPLIER * zoom_multiplier) + x_offset;
        double double_y = sin(degree * degree_multiplier) * (max_size * MAIN_CIRCLE_RADIUS_MULTIPLIER * zoom_multiplier) + y_offset;
        int x = (int) double_x;
        int y = (int) double_y;

        // int x = (int) (cos(degree * degree_multiplier));
        // int y = (int) (sin(degree * degree_multiplier));

        //Point *center = (Point *) malloc(sizeof(Point));
        // center = { .x = x, .y = y };
        ((Vertex_Data *) p->data)->center->x = x;
        ((Vertex_Data *) p->data)->center->y = y;

        //printf("point %d: degree: %lf, center: (%lf; %lf)\n\n", degree_multiplier, degree * degree_multiplier, cos(degree * degree_multiplier), sin(degree * degree_multiplier));

        transfrom_point(((Vertex_Data *) p->data)->center, window_surface);

        degree_multiplier++;
        p = p->next_node;
    }
}

/**
 * @brief Megrajzolja a gráfpontokat. Hasonló a draw_main_circle() függvényhez.
 * 
 * @param vertices A pontokat tartalmazó lista
 * @see draw_main_circle
 */
void draw_vertices(List *vertices, SDL_Renderer *renderer, int radius) {
    // int size = get_max_size(window_surface);
    Node *p = vertices->head_node;
    // int radius = (int) (size * VERTEX_CIRCLE_RADIUS_MULTIPLIER);

    while (p != NULL) {
        Point *center = ((Vertex_Data *) p->data)->center;
        bool selected = ((Vertex_Data *) p->data)->selected;
        selected ? filledCircleRGBA(renderer, center->x, center->y, radius, SELECTED_R, SELECTED_G, SELECTED_B, SELECTED_ALPHA) : filledCircleRGBA(renderer, center->x, center->y, radius, VERTEX_R, VERTEX_G, VERTEX_B, VERTEX_ALPHA);
        
#ifdef DEBUG
        int min_x = center->x - radius;
        int max_x = center->x + radius;
        int min_y = center->y - radius;
        int max_y = center->y + radius;
        rectangleRGBA(renderer, min_x, min_y, max_x, max_y, DEBUG_R, DEBUG_G, DEBUG_B, DEBUG_ALPHA);
#endif

        p = p->next_node;
    }
}

Node *get_clicked_node(SDL_Event *event, List *vertices, int radius) {
    Point click = { .x = event->button.x, .y = event->button.y };
    // int radius = (int) (size * VERTEX_CIRCLE_RADIUS_MULTIPLIER);
    Node *p = vertices->head_node;

    while (p != NULL) {
        Point *center = ((Vertex_Data *) p->data)->center;
        int min_x = center->x - radius;
        int max_x = center->x + radius;
        int min_y = center->y - radius;
        int max_y = center->y + radius;

        bool collision_x = click.x >= min_x && click.x <= max_x;
        bool collision_y = click.y >= min_y && click.y <= max_y;
        
        if (collision_x && collision_y) return p;

        p = p->next_node;
    }

    return p;
}

void select_node(Node* node) {
    ((Vertex_Data *) node->data)->selected = true;
}

void deselect_original_node(Node* node) {
    // ((Vertex_Data *) node->data)->selected = false;
    ((Vertex_Data *) *((Vertex_Data **) node->data))->selected = false;
}

void deselect_node(Node* node) {
    ((Vertex_Data *) node->data)->selected = false;
    // ((Vertex_Data *) *((Vertex_Data **) node->data))->selected = false;
}

void toggle_node_selection(Node* node) {
    ((Vertex_Data *) node->data)->selected = !(((Vertex_Data *) node->data)->selected);
}

int get_radius(int max_size, double mode_multiplier, double zoom_multiplier) {
    return (int) (max_size * mode_multiplier * zoom_multiplier);
}

