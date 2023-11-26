/**
 * @brief Grafikai műveletek
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
 * @brief Létrehoz egy gráf pontot.
 * 
 * Létrehoz egy új vertex_node-ot és beállítja az adatait, majd hozzáadja a pontokat a létező pontokat tároló listához.
 * 
 * @param vertices Létező pontok listája
 * @param vertex_id Az azonosítókat követő változó
 */
void create_vertex(Vertex_List *vertices, size_t vertex_id, int radius, int vertex_red, int vertex_green, int vertex_blue, int vertex_alpha) {
    Vertex_Node *vertex_node = new_vertex_node();
    vertex_node->vertex_data.id = vertex_id;
    vertex_node->vertex_data.radius = radius;
    vertex_node->vertex_data.selected = 0;
    vertex_node->vertex_data.red = vertex_red;
    vertex_node->vertex_data.green = vertex_green;
    vertex_node->vertex_data.blue = vertex_blue;
    vertex_node->vertex_data.alpha = vertex_alpha;
    vertex_node->vertex_data.visited = false;
    // printf("vertex node next: %p\n", vertex_node->next_node);
    vertex_list_push(vertices, vertex_node);
}

/**
 * @brief Beállítja a pontoknak a koordinátáit attól függően, hogy hány pont létezik.
 * 
 * A pontokat egy szabályos körben rendezi el, a pontok számától függően. A pontok elhelyezése függ az ablak méretétől, hogy mindig kiférjen az egész gráf
 *
 * @see transform_point
 * 
 * @param vertices Pontok listája
 * @param window_surface Ablak felszín
 * @param max_size Ablak mérete
 * @param zoom_multiplier Zoom
 * @param x_offset X elmozdulás
 * @param y_offset Y elmozdulás
 */
void set_vertices_coords(Vertex_List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offset, int y_offset, double main_circle_radius_multiplier) {
    // printf("start\n");
    double degree = (2 * 3.14159265359) / vertices->size;
    size_t degree_multiplier = 1;
    Vertex_Node *iterator = vertices->head;
    // printf("iterator: %p\n", iterator);

    while (iterator != NULL) {
        double double_x = cos(degree * degree_multiplier) * (max_size * main_circle_radius_multiplier * zoom_multiplier) + x_offset;
        double double_y = sin(degree * degree_multiplier) * (max_size * main_circle_radius_multiplier * zoom_multiplier) + y_offset;
        int x = (int) double_x;
        int y = (int) double_y;
        iterator->vertex_data.center.x = x;
        iterator->vertex_data.center.y = y;

        // printf("valtozok\n");


        transfrom_point(&(iterator->vertex_data.center), window_surface);

        // printf("transform point\n");

        degree_multiplier++;
        // printf("iterator next: %p\n", iterator->next_node);
        iterator = iterator->next_node;
        // printf("new iterator: %p\n", iterator);
    }

    // printf("coords set vege\n");
}


/**
 * @brief Kiszámolja egy pont sugarát.
 * 
 * A pontok sugara függ az ablak mérettől, a zoomolástól és attól, hogy milyen típusú a pont.
 * 
 * @param max_size Képrenyő mérete
 * @param mode_multiplier Pont típusának szorzója
 * @param zoom_multiplier Zoom
 * @return int A pont sugara
 */
int get_radius(int max_size, double mode_multiplier, double zoom_multiplier) {
    return (int) (max_size * mode_multiplier * zoom_multiplier);
}

/**
 * @brief Megrajzolja a gráfpontokat. Hasonló a draw_main_circle() függvényhez.
 * 
 * @param vertices A pontokat tartalmazó lista
 * @see draw_main_circle
 */
void draw_vertices(Vertex_List *vertices, SDL_Renderer *renderer) {
    Vertex_Node *iterator = vertices->head;

    while (iterator != NULL) {
        Point center = iterator->vertex_data.center;
        Vertex_Data vd = iterator->vertex_data;

        filledCircleRGBA(renderer, center.x, center.y, vd.radius, vd.red, vd.green, vd.blue, vd.alpha);
        //circleRGBA(renderer, center.x, center.y, vd.radius, SHADING_R, SHADING_G, SHADING_B, SHADING_ALPHA);
        
        iterator = iterator->next_node;
    }
}

/**
 * @brief Megkeresi azt a Vertex_Node-ot, amire kattintott a felhasználó.
 * 
 * @param event SDL_Event
 * @param vertices Létező pontok listája
 * @return Vertex_Node* 
 */
Vertex_Node *get_clicked_node(SDL_Event *event, Vertex_List *vertices) {
    Point click = { .x = event->button.x, .y = event->button.y };
    Vertex_Node *iterator = vertices->head;

    while (iterator != NULL) {
        Point center = iterator->vertex_data.center;
        int radius = iterator->vertex_data.radius;
        int min_x = center.x - radius;
        int max_x = center.x + radius;
        int min_y = center.y - radius;
        int max_y = center.y + radius;

        bool collision_x = click.x >= min_x && click.x <= max_x;
        bool collision_y = click.y >= min_y && click.y <= max_y;
        
        if (collision_x && collision_y) return iterator;

        iterator = iterator->next_node;
    }

    return iterator;
}

/**
 * @brief Kijelöli a megadott Vertex_Node-ot
 * 
 * @param selection Kijelölt pontok listája
 * @param vertex_node Pont
 */
void select_vertex(Vertex_Pointer_List *selection, Vertex_Node *vertex_node, int selected_red, int selected_green, int selected_blue, int selected_alpha) {
    vertex_node->vertex_data.selected = 1;
    vertex_node->vertex_data.red = selected_red;
    vertex_node->vertex_data.green = selected_green;
    vertex_node->vertex_data.blue = selected_blue;
    vertex_node->vertex_data.alpha = selected_alpha;
    
    Vertex_Pointer_Node *vp = new_vertex_pointer_node();
    vp->vertex_node = vertex_node;
    vertex_pointer_list_push(selection, vp);
}

/**
 * @brief Megszünteti a megadott Vertex_Node_Pointer által mutatott Vertex_Node kijelölését
 * 
 * @param selection Kijelölt pontok listája
 * @param vertex_pointer_node Pont mutató
 */
void unselect_vertex(Vertex_Pointer_List *selection, Vertex_Pointer_Node *vertex_pointer_node, int vertex_red, int vertex_green, int vertex_blue, int vertex_alpha) {
    vertex_pointer_node->vertex_node->vertex_data.selected = 0;
    vertex_pointer_node->vertex_node->vertex_data.red = vertex_red;
    vertex_pointer_node->vertex_node->vertex_data.green = vertex_green;
    vertex_pointer_node->vertex_node->vertex_data.blue = vertex_blue;
    vertex_pointer_node->vertex_node->vertex_data.alpha = vertex_alpha;

    vertex_pointer_list_pop(selection, vertex_pointer_node);
}

/**
 * @brief Létrehoz egy gráf élt
 * @todo Megcsinálni az irányított éleket
 * 
 * @param edges Létező élek listája
 * @param to Melyik pontból
 * @param from Melyik pontba
 * @param directed Irányított él-e?
 */
void create_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, int edge_red, int edge_green, int edge_blue, int edge_alpha, int edge_width) {
    Edge_Node *edge_node = new_edge_node();
    edge_node->edge.to = to;
    edge_node->edge.from = from;
    edge_node->edge.red = edge_red;
    edge_node->edge.green = edge_green;
    edge_node->edge.blue = edge_blue;
    edge_node->edge.alpha = edge_alpha;
    edge_node->edge.width = edge_width;
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

/**
 * @brief Kiszínezi a megadott node-hoz tartozó éleket a megadott színre
 * 
 * @param edges Élek listája
 * @param vertex_node Gráf pont
 * @param edge_red R
 * @param edge_green G 
 * @param edge_blue B
 * @param edge_alpha A
 */
void toggle_select_edges(Edge_List *edges, Vertex_Node *vertex_node, int edge_red, int edge_green, int edge_blue, int edge_alpha) {
    Edge_Node *edges_iterator = edges->head;

    while (edges_iterator != NULL) {
        if (edges_iterator->edge.to == vertex_node || edges_iterator->edge.from == vertex_node) {
            edges_iterator->edge.red = edge_red;
            edges_iterator->edge.green = edge_green;
            edges_iterator->edge.blue = edge_blue;            
            edges_iterator->edge.alpha = edge_alpha;
        }

        edges_iterator = edges_iterator->next_node;
    }
}

/**
 * @brief A megadott lista összes elemének visited adatát false-ra állítja
 * 
 * @param vertices Gráf pontok listája
 */
void unvisit_vertices(Vertex_List *vertices) {
    Vertex_Node *vertices_iterator = vertices->head;

    while (vertices_iterator != NULL) {
        vertices_iterator->vertex_data.visited = false;
        vertices_iterator = vertices_iterator->next_node;
    }
}

/**
 * @brief Bejárja szélességileg a gráfot és kijelöli az összes elérhető pontot a megadott kezdőponttól
 * 
 * @param vertices Gráf pontok listája
 * @param vertex_node Kezdő pont
 * @param edges Gráf élek listája
 * @param selection Kijelölt pontok listája
 * @param selected_red Kijelölés piros
 * @param selected_green Kijelölés zöld
 * @param selected_blue Kijelölés kék
 * @param selected_alpha Kijelölés átlátszóság
 */
void depth_first_traverse(Vertex_List *vertices, Vertex_Node *vertex_node, Edge_List *edges, Vertex_Pointer_List *selection, int selected_red, int selected_green, int selected_blue, int selected_alpha) {
    Vertex_Pointer_List *unvisited_vertices = new_vertex_pointer_list();

    vertex_node->vertex_data.visited = true;

    bool traversing = true;

    while (traversing) {
        Edge_Node *edges_iterator = edges->head;
        
        while (edges_iterator != NULL) {
            if (edges_iterator->edge.from == vertex_node && !(edges_iterator->edge.to->vertex_data.visited)) {
                Vertex_Pointer_Node *unvisited_vertex_pointer = new_vertex_pointer_node();

                unvisited_vertex_pointer->vertex_node = edges_iterator->edge.to;
                vertex_pointer_list_push(unvisited_vertices, unvisited_vertex_pointer);
            }
            
            edges_iterator = edges_iterator->next_node;
        }

        if (unvisited_vertices->head != NULL) {
            vertex_node = unvisited_vertices->tail->vertex_node;
            vertex_node->vertex_data.visited = true;
            select_vertex(selection, vertex_node, selected_red, selected_green, selected_green, selected_alpha);
            vertex_pointer_list_pop(unvisited_vertices, unvisited_vertices->tail);

        } else {
            traversing = false;
        }
    }

    destroy_vertex_pointer_list(unvisited_vertices);

    unvisit_vertices(vertices);
}

/**
 * @brief Bejárja szélességileg a gráfot és kijelöli az összes elérhető pontot a megadott kezdőponttól
 * 
 * @param vertices Gráf pontok listája
 * @param vertex_node Kezdő pont
 * @param edges Gráf élek listája
 * @param selection Kijelölt pontok listája
 * @param selected_red Kijelölés piros
 * @param selected_green Kijelölés zöld
 * @param selected_blue Kijelölés kék
 * @param selected_alpha Kijelölés átlátszóság
 */
void breadth_first_traverse(Vertex_List *vertices, Vertex_Node *vertex_node, Edge_List *edges, Vertex_Pointer_List *selection, int selected_red, int selected_green, int selected_blue, int selected_alpha) {
    Vertex_Pointer_List *unvisited_vertices = new_vertex_pointer_list();

    vertex_node->vertex_data.visited = true;

    bool traversing = true;

    while (traversing) {
        Edge_Node *edges_iterator = edges->head;
        
        while (edges_iterator != NULL) {
            if (edges_iterator->edge.from == vertex_node && !(edges_iterator->edge.to->vertex_data.visited)) {
                Vertex_Pointer_Node *unvisited_vertex_pointer = new_vertex_pointer_node();

                unvisited_vertex_pointer->vertex_node = edges_iterator->edge.to;
                vertex_pointer_list_push(unvisited_vertices, unvisited_vertex_pointer);
            }
            
            edges_iterator = edges_iterator->next_node;
        }

        if (unvisited_vertices->head != NULL) {
            vertex_node = unvisited_vertices->head->vertex_node;
            vertex_node->vertex_data.visited = true;
            select_vertex(selection, vertex_node, selected_red, selected_green, selected_green, selected_alpha);
            vertex_pointer_list_pop(unvisited_vertices, unvisited_vertices->head);

        } else {
            traversing = false;
        }
    }

    destroy_vertex_pointer_list(unvisited_vertices);

    unvisit_vertices(vertices);
}