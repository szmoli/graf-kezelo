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
    Node *neighbour_node = copy_node(node);
    List *neighbour_list = new_list();
    
    list_push(vertexes, node);
    list_push(neighbour_list, neighbour_node);
    array_push(neighbour_arr, neighbour_list);
}

List *get_neighbour_list(Array *neighbour_arr, Node *node) {
    for (size_t i = 0; i < neighbour_arr->size; i++) {
        if ((*((Vertex_Data **) ((List*) neighbour_arr->array[i])->head_node->data)) == (Vertex_Data *) node->data) return neighbour_arr->array[i];
    }
}

//! @todo befejezni a set_edge függvényt
void set_edge(Array *neighbour_arr, Node *node1, Node *node2) {
    List *list_a;
    List *list_b;
}

//! @todo Megírni a többi gráfpont-kezelő függvényt