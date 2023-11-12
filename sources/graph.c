/**
 * @brief Ez a fájl a gráfműveletekhez tartozó függvényeket tartalmazza.
 */

#include "graph.h"

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
    // Vertex_Data **orig_data = (Vertex_Data **) malloc(sizeof(Vertex_Data *)); 
    // orig_data = (Vertex_Data **) &(node->data); // pointer az eredeti adatra
    Node *neighbour_node = new_node(&(node->data));
    List *neighbour_list = new_list();
    
    list_push(vertexes, node);
    list_push(neighbour_list, neighbour_node);
    array_push(neighbour_arr, neighbour_list);
}