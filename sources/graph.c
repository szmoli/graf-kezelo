#include "graph.h"
#include "debugmalloc.h"
#include <stdlib.h>

Graph *alloc_graph() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    
    graph->vertex_count = 0;
    graph->vertices = (Vertex **) malloc(graph->vertex_count * sizeof(Vertex *));

    return graph;
}

void free_graph(Graph *graph) {
    free(graph->vertices);
    graph->vertices = NULL;

    free(graph);
    graph = NULL;
}

// felszabadítás a hívó dolga
// void copy_vertices(Vertex *target, int target_size, Graph *origin) {
//     Vertex *target = (Vertex *) malloc(target_size * sizeof(Vertex));

//     for (int i = 0; i < origin->vertex_count; i++) {
//         target[i] = origin->vertices[i];
//     }
// }

Vertex *alloc_vertex() {
    return (Vertex *) malloc(sizeof(Vertex));
}

void free_vertex(Vertex *vertex) {
    free(vertex);
    vertex = NULL;
}

void copy_vertices(Vertex **target_vertices, Vertex **origin_vertices, int vertex_count) {
    for (int i = 0; i < vertex_count; i++) {
        target_vertices[i] = origin_vertices[i];
    }
}

void free_vertices(Vertex **vertices, int vertex_count) {
    for (int i = 0; i < vertex_count; i++)    {
        free(vertices[i]);
        vertices[i] = NULL;
    }

    free(vertices);
    vertices = NULL;
}

void set_vertex(Vertex *vertex, int *id) {
    vertex->id = id++;
    vertex->x = 100;
    vertex->y = 100;
    vertex->radius = 25;
    vertex->edge_count = 0;
    vertex->edges = NULL;
}

void add_vertex(Graph *graph) {
    Vertex *new_vertex = alloc_vertex();
    int old_vertex_count = graph->vertex_count;
    graph->vertex_count++;
    Vertex **new_vertices = (Vertex **) malloc(graph->vertex_count * sizeof(Vertex *));

    copy_vertices(new_vertices, graph->vertices, old_vertex_count);
    // TODO: set vertex
    new_vertices[old_vertex_count] = new_vertex;

    free_vertices(graph->vertices, graph->vertex_count);
    free(new_vertex);
}

// Vertex *get_vertex(Graph *graph, int vertex_id) {
//     bool found = false;
//     int i = 0;
    
//     while (i < graph->vertex_count && !found) {
//         if (graph->vertices[i].id == vertex_id) return &graph->vertices[i];
//     }

//     return NULL;
// }

Edge *alloc_edge() {
    return (Edge *) malloc(sizeof(Edge));
}

void free_edge(Edge *edge) {
    free(edge);
    edge = NULL;
}

// void add_edge(Graph *graph, int target_vertex_id, int origin_vertex_id) {
//     Edge *edge = alloc_edge();

//     edge->target_vertex_id = target_vertex_id;
//     edge->origin_vertex_id = origin_vertex_id;

//     Vertex *target_vertex = get_vertex(graph, target_vertex_id);
//     Vertex *origin_vertex = get_vertex(graph, origin_vertex_id);
//     int old_target_edge_count = target_vertex->edge_count;
//     int old_origin_edge_count = origin_vertex->edge_count;
//     target_vertex->edge_count++;
//     origin_vertex->edge_count++;

//     target_vertex->edges[old_target_edge_count] = edge;
//     origin_vertex->edges[old_origin_edge_count] = edge;
// }

