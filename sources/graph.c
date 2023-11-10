/**
 * @file graph.c
 * @author Szmoleniczki Ákos
 * @brief Ez a fájl a gráfműveletekhez tartozó függvényeket tartalmazza.
 * @version 0.1
 * @date 2023-11-10
 */

#include "typedefs.h"
#include "linked_list.h"
#include "dynamic_array.h"
#include "debugmalloc.h"
#include <memory.h>
#include <stdlib.h>

/**
 * @todo Befejezni ezt a függvényt. Kijavítani a hibákat. Dokumentációt írni.
 * @brief 
 * 
 * @param neighbour_arr 
 * @param vertexes 
 * @param data 
 */
void new_vertex(Array *neighbour_arr, List *vertexes, Vertex_Data *data) {
    Node *node = new_node(data);
    Node **orig_node = (Node **) malloc(sizeof(Node *));
    orig_node = &(node);
    Node *neighbour_node = new_node(orig_node);
    List *neighbour_list = new_list();
    
    list_push(vertexes, node);
    list_push(neighbour_list, neighbour_node);
    array_push(neighbour_arr, neighbour_list);
}