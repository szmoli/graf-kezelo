#pragma once

typedef struct Edge {
    int id;
    int x, y;
    int width;
    int origin_vertex_id, target_vertex_id;
} Edge;

typedef struct Vertex {
    int id;
    int x, y;
    int edge_count;
    double radius;
    Edge **edges;
} Vertex;

typedef struct Graph {
    int vertex_count;
    Vertex **vertices;
} Graph;

Graph *alloc_graph();
void free_graph(Graph *graph);