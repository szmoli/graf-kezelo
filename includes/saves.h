/**
 * @brief Mentések kezeléséhez szükséges függvények
 */

#pragma once

#include "typedefs.h"
#include "lists.h"

#include <stdlib.h>
#include <stdio.h>
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
char *get_date_time_str();

/**
 * @brief Mentésfájl nevet generál
 * 
 * @param saves_dir Mentések mappája
 * @param extension Fájl kiterjesztés
 * @param time_str Időpont stringje
 * @return char* Mentés fájl neve
 */
char *get_save_file_path(char *saves_dir, char *extension, char *time_str);

/**
 * @brief Ellenőrzi, hogy van-e már a programnak mentések mappája, ha nincs akkor létrehozza
 * 
 * @param saves_dir Mappa elérési útvonala
 */
void check_and_make_saves_dir(char *saves_dir);

/**
 * @brief Elmenti a megadott listát a megadott helyre
 * 
 * @param list Lista
 * @param save_file Mentés fájl elérési útvonala
 */
void save_vertices_and_selection(Vertex_List *list, FILE *save_file);

/**
 * @brief Elmenti a megadott listát a megadott helyre
 * 
 * @param list Lista
 * @param save_file Mentés fájl elérési útvonala
 */
void save_edges(Edge_List *list, FILE *save_file);

/**
 * @brief Elmenti a teljes gráfot
 * 
 * @param vertices Gráf pontok listája
 * @param edges Gráf élek listája
 * @param vertices_save_path Gráf pontok mentési helye
 * @param edges_save_path Gráf élek mentési helye
 * @param graph_save_path Gráf mentési helye
 */
void save_graph(Vertex_List *vertices, Edge_List *edges, char *vertices_save_path, char *edges_save_path, char *graph_save_path);

/**
 * @brief Ellenőtzi, hogy megfelelő fájlt kapott-e a program
 * 
 * @param file_path Fájl elérési útvonala
 * @param graph_file_estension Helyes fájlkiterjesztés
 * @return true Ha a megadott fájl kiterjesztése egyezik a helyes kiterjesztéssel
 * @return false He nem egyeznek
 */
bool is_valid_graph_file(char *file_path, char *graph_file_estension);

/**
 * @brief Kiveszi a dátumot és időt a megnyitott fájl elérési útvonalából
 * 
 * @param file_path Elérési útvonal
 * @return char* Dátum és idő string
 */
char *get_date_time_str_from_file_path(char *file_path);

/**
 * @brief Betölti a gráf pontokat
 * 
 * @param vertices Gráf pontok listája
 * @param file Gráf pontok mentés fájlja
 * @param selection Kijelölt pontok listája
 * @param max_id Gráf pont azonosítók változója
 */
void load_vertices_and_selection(Vertex_List *vertices, Vertex_Pointer_List *selection, FILE *file, int *max_id);

/**
 * @brief Betölti a gráf éleket
 * 
 * @param edges Gráf élek listája
 * @param vertices Gráf pontok listája
 * @param file Gráf élek mentés fájlja
 */
void load_edges(Edge_List *edges, Vertex_List *vertices, FILE *file);

/**
 * @brief Betölti az egész elmentett gráfot egy fájlból
 * 
 * @param vertices Gráf pontok listája
 * @param edges Gráf élek listája
 * @param selection Kijelölt pontok listája
 * @param vertices_save_path  Gráf pontok mentésének elérési útvonala
 * @param edges_save_path Gráf élek mentésének elérési útvonala
 * @param max_id Gráf pont azonosítók változója
 */
void load_graph(Vertex_List *vertices, Edge_List *edges, Vertex_Pointer_List *selection, char *vertices_save_path, char *edges_save_path, int *max_id);