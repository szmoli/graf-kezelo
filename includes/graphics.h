/**
 * @brief Grafikai műveletek
 * 
 */

#pragma once

#include "debugmalloc.h"
#include "typedefs.h"
#include "lists.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <stdbool.h>
#include <stdio.h>
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
bool config_sdl(SDL_Window **window, SDL_Surface **window_surface, SDL_Renderer **renderer);

/**
 * @brief Leállítja az SDL ablakot és a főciklus változóját false-ra állítja.
 * 
 * @param window Ablak változó.
 * @param renderer Renderer változó.
 * @param loop A főciklus bentmaradás feltételének változója.
 */
void quit_sdl(SDL_Window **window, SDL_Renderer **renderer, bool *loop);

/**
 * @brief Egy homogén koordinátát SDL-szerű koordinátává alakít.
 * 
 * @param point Pont, aminek a koordinátáit átalakítja
 * @param window_surface Ablak felszín
 */
void transfrom_point(Point *point, SDL_Surface *window_surface);

/**
 * @brief Visszaadja az ablak szélességét vagy magasságát attól függően, hogy melyik a nagyobb.
 * 
 * @param window_surface Ablakfelület változó
 * @return int A nagyobb érték
 */
int get_max_size(SDL_Surface *window_surface);

/**
 * @brief Létrehoz egy gráf pontot.
 * 
 * Létrehoz egy új vertex_node-ot és beállítja az adatait, majd hozzáadja a pontokat a létező pontokat tároló listához.
 * 
 * @param vertices Létező pontok listája
 * @param vertex_id Az azonosítókat követő változó
 * @param radius Sugár
 * @param vertex_red Piros szín
 * @param vertex_green Zöld szín
 * @param vertex_blue Kék szín
 * @param vertex_alpha Átlátszóság
 */
void create_vertex(Vertex_List *vertices, int *vertex_id, int radius, int vertex_red, int vertex_green, int vertex_blue, int vertex_alpha);

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
 * @param main_circle_radius_multiplier Körvonal sugarának szorzója
 */
void set_vertices_coords(Vertex_List *vertices, SDL_Surface *window_surface, int max_size, double zoom_multiplier, int x_offset, int y_offset, double main_circle_radius_multiplier);

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
int get_radius(int max_size, double mode_multiplier, double zoom_multiplier);

/**
 * @brief Megrajzolja a gráfpontokat. Hasonló a draw_main_circle() függvényhez.
 * 
 * @param vertices A pontokat tartalmazó lista
 * @param renderer SDL_Renderer
 * @see draw_main_circle
 */
void draw_vertices(Vertex_List *vertices, SDL_Renderer *renderer);

/**
 * @brief Megkeresi azt a Vertex_Node-ot, amire kattintott a felhasználó.
 * 
 * @param event SDL_Event
 * @param vertices Létező pontok listája
 * @return Vertex_Node* 
 */
Vertex_Node *get_clicked_node(SDL_Event *event, Vertex_List *vertices);

/**
 * @brief Kijelöli a megadott Vertex_Node-ot
 * 
 * @param selection Kijelölt pontok listája
 * @param vertex_node Pont
 * @param selected_red Piros szín
 * @param selected_green Zöld szín
 * @param selected_blue Kék szín
 * @param selected_alpha Átlátszóság
 */
void select_vertex(Vertex_Pointer_List *selection, Vertex_Node *vertex_node, int selected_red, int selected_green, int selected_blue, int selected_alpha);

/**
 * @brief Megszünteti a megadott Vertex_Node_Pointer által mutatott Vertex_Node kijelölését
 * 
 * @param selection Kijelölt pontok listája
 * @param vertex_pointer_node Pont mutató
 * @param vertex_red Piros szín
 * @param vertex_green Zöld szín
 * @param vertex_blue Kék szín
 * @param vertex_alpha Átlátszó
 */
void unselect_vertex(Vertex_Pointer_List *selection, Vertex_Pointer_Node *vertex_pointer_node, int vertex_red, int vertex_green, int vertex_blue, int vertex_alpha);

/**
 * @brief Létrehoz egy gráf élt
 * 
 * @param edges Létező élek listája
 * @param to Melyik pontból
 * @param from Melyik pontba
 * @param edge_red Piros színe
 * @param edge_green Zöld színe
 * @param edge_blue Kék színe
 * @param edge_alpha Átlátszóság
 * @param edge_width Szélesség
 */
void create_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from, int edge_red, int edge_green, int edge_blue, int edge_alpha, int edge_width);

/**
 * @brief Kirajzolja az éleket
 * 
 * @param edges Létező élek listája
 * @param renderer SDL_Renderer
 */
void draw_edges(Edge_List *edges, SDL_Renderer *renderer);

/**
 * @brief Megkeresi a két pont közt húzott élt
 * 
 * @param edges Létező élek listája
 * @param to Melyik pontból
 * @param from Melyik pontba
 * @return Edge_Node* NULL, ha nincs köztük él
 */
Edge_Node *get_edge(Edge_List *edges, Vertex_Node *to, Vertex_Node *from);

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
void toggle_select_edges(Edge_List *edges, Vertex_Node *vertex_node, int edge_red, int edge_green, int edge_blue, int edge_alpha);

/**
 * @brief A megadott lista összes elemének visited adatát false-ra állítja
 * 
 * @param vertices Gráf pontok listája
 */
void unvisit_vertices(Vertex_List *vertices);

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
void depth_first_traverse(Vertex_List *vertices, Vertex_Node *vertex_node, Edge_List *edges, Vertex_Pointer_List *selection, int selected_red, int selected_green, int selected_blue, int selected_alpha);

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
void breadth_first_traverse(Vertex_List *vertices, Vertex_Node *vertex_node, Edge_List *edges, Vertex_Pointer_List *selection, int selected_red, int selected_green, int selected_blue, int selected_alpha);