#pragma once

typedef struct Edge {

} Edge;

typedef struct Vertex {
    int id;
    int x, y;
    double radius;
    int *connections; // connections by id
} Vertex;

typedef struct Graph {
    int node_count;
    Node *nodes;
} Graph;

Graph *alloc_graph();
void free_graph(Graph *graph);