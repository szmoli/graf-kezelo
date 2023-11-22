/**
 * @brief Ez a fájl tartalmazza a lista típus definíciókat.
 */

#pragma once

#include <stdbool.h>

/**
 * @brief 2D-s pont
 * 
 */
typedef struct Point {
    int x;
    int y;
} Point;

/**
 * @brief Gráf pont adat
 * 
 */
typedef struct Vertex_Data {
    int id;
    bool selected;
    Point center;
    int red;
    int green;
    int blue;
    int alpha;
    int radius;
} Vertex_Data;

/**
 * @brief Gráf pont listaelem
 * 
 */
typedef struct Vertex_Node {
    Vertex_Data vertex_data;
    struct Vertex_Node *next_node;
} Vertex_Node;

/**
 * @brief Gráf pont lista
 * 
 */
typedef struct Vertex_List {
    int size;
    Vertex_Node *head;
    Vertex_Node *tail;
} Vertex_List;

/**
 * @brief Gráf él
 * 
 */
typedef struct Edge {
    Vertex_Node *from;
    Vertex_Node *to;
    bool directed;
    int red;
    int green;
    int blue;
    int alpha;
    int width;
} Edge;

/**
 * @brief Gráf él listaelem
 * 
 */
typedef struct Edge_Node {
    Edge edge;
    struct Edge_Node *next_node;
} Edge_Node;

/**
 * @brief Gráf él lista
 * 
 */
typedef struct Edge_List {
    int size;
    Edge_Node *head;
    Edge_Node *tail;
} Edge_List;

/**
 * @brief Gráf pont mutató listaelem
 * 
 */
typedef struct Vertex_Pointer_Node {
    Vertex_Node *vertex_node;
    struct Vertex_Pointer_Node *next_node;
} Vertex_Pointer_Node;

/**
 * @brief Gráf pont
 * 
 */
typedef struct Vertex_Pointer_List {
    int size;
    Vertex_Pointer_Node *head;
    Vertex_Pointer_Node *tail;
} Vertex_Pointer_List;