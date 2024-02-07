/**
 * @brief Listaműveletek
 */

#pragma once

#include "debugmalloc.h"
#include "typedefs.h"

/**
 * @brief Létrehoz a memóriában egy új gráf pont listaelemet.
 * 
 * @return Vertex_Node* A létrehozott listaelem címe
 */
Vertex_Node *new_vertex_node();

/**
 * @brief Létrehoz a memóriában egy új gráf él listaelemet.
 * 
 * @return Edge_Node* A létrehozott listaelem címe
 */
Edge_Node *new_edge_node();

/**
 * @brief Létrehoz a memóriában egy új gráf pont mutató listaelemet.
 * 
 * @return Vertex_Pointer_Node* A létrehozott listaelem címe
 */
Vertex_Pointer_Node *new_vertex_pointer_node();

/**
 * @brief Létrehoz a memóriában egy új gráf pont listát.
 * 
 * @return Vertex_List* A létrehozott lista címe.
 */
Vertex_List *new_vertex_list();

/**
 * @brief Létrehoz a memóriában egy új gráf él listát.
 * 
 * @return Edge_List* A létrehozott lista címe.
 */
Edge_List *new_edge_list();

/**
 * @brief Létrehoz a memóriában egy új gráf pont mutató listát.
 * 
 * @return Vertex_Pointer_List* A létrehozott lista címe.
 */
Vertex_Pointer_List *new_vertex_pointer_list();

/**
 * @brief Felszabadítja a megadott gráf pont listát
 * 
 * @param list Felszabadítandó lista címe
 */
void destroy_vertex_list(Vertex_List *list);

/**
 * @brief Kiüríti a megadott gráf pont listát
 * 
 * @param list Kiürítendő lista címe
 */
void clear_vertex_list(Vertex_List *list);

/**
 * @brief Felszabadítja a megadott gráf él listát
 * 
 * @param list Felszabadítandó lista címe
 */
void destroy_edge_list(Edge_List *list);

/**
 * @brief Kiüríti a megadott gráf él listát
 * 
 * @param list Kiürítendő lista címe
 */
void clear_edge_list(Edge_List *list);

/**
 * @brief Felszabadítja a megadott gráf pont mutató listát
 * 
 * @param list Felszabadítandó lista címe
 */
void destroy_vertex_pointer_list(Vertex_Pointer_List *list);

/**
 * @brief Kiüríti a megadott gráf pont mutató listát
 * 
 * @param list Kiürítendő lista címe
 */
void clear_vertex_pointer_list(Vertex_Pointer_List *list);

/**
 * @brief Hozzáad a megadott lista végéhez egy listaelemet.
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void vertex_list_push(Vertex_List *list, Vertex_Node *node);

/**
 * @brief Hozzáad a megadott lista végéhez egy listaelemet.
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void edge_list_push(Edge_List *list, Edge_Node *node);

/**
 * @brief Hozzáad a megadott lista végéhez egy listaelemet.
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void vertex_pointer_list_push(Vertex_Pointer_List *list, Vertex_Pointer_Node *node);

/**
 * @brief Kitörli a megadott listából a megadott listaelemet
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void vertex_list_pop(Vertex_List *list, Vertex_Node *node);

/**
 * @brief Kitörli a megadott listából a megadott listaelemet
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void edge_list_pop(Edge_List *list, Edge_Node *node);

/**
 * @brief Kitörli a megadott listából a megadott listaelemet
 * 
 * @param list Lista címe
 * @param node Listaelem címe
 */
void vertex_pointer_list_pop(Vertex_Pointer_List *list, Vertex_Pointer_Node *node);

/**
 * @brief Kiírja a megadott lista összes elemét
 * 
 * @param list Lista címe
 */
void print_vertex_list(Vertex_List *list);

/**
 * @brief Kiírja a megadott lista összes elemét
 * 
 * @param list Lista címe
 */
void print_edge_list(Edge_List *list);

/**
 * @brief Kiírja a megadott lista összes elemét
 * 
 * @param list Lista címe
 */
void print_vertex_pointer_list(Vertex_Pointer_List *list);

/**
 * @brief Megkeresi egy Vertex_Pointer_List-ben a megadott Vertex_Node-ra mutató listaelemet
 * 
 * @param list A lista amiben keres
 * @param vertex_node A Vertex_Node, amit keres
 * @return Vertex_Pointer_Node* NULL, ha nem talált egyezést
 */
Vertex_Pointer_Node *get_vertex_pointer_node(Vertex_Pointer_List *list, Vertex_Node *vertex_node);

/**
 * @brief Visszaadja a megadott listából azt az elemet, aminek azonosítója megegyezik a megadott azonosítóval
 * 
 * @param list 
 * @param id 
 * @return Vertex_Node* NULL, ha nincs a listában
 */
Vertex_Node *get_vertex_node_by_id(Vertex_List *list, int id);