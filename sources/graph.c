#include "graph.h"
#include "debugmalloc.h"
#include <stdlib.h>

Graph *alloc_graph() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    
    graph->node_count = 0;
    graph->nodes = (Node *) malloc(sizeof(Node));

    return graph;
}

void free_graph(Graph *graph) {
    free(graph->nodes);
    graph->nodes = NULL;

    free(graph);
    graph = NULL;
}