#include "typedefs.h"
#include "linked_list.h"
#include "dynamic_array.h"
#include "debugmalloc.h"
#include <memory.h>
#include <stdlib.h>

void new_vertex(Array *neighbour_arr, List *vertexes, Vertex_Data *data);
List *get_neighbour_list(Array *neighbour_arr, Node *node);
void set_edge(Array *neighbour_arr, Node *node_a, Node *node_b);