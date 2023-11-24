#include "debugmalloc.h"
#include "typedefs.h"

Vertex_Node *new_vertex_node();
Edge_Node *new_edge_node();
Vertex_Pointer_Node *new_vertex_pointer_node();
Vertex_List *new_vertex_list();
Edge_List *new_edge_list();
Vertex_Pointer_List *new_vertex_pointer_list();
void destroy_vertex_list(Vertex_List *list);
void clear_vertex_list(Vertex_List *list);
void destroy_edge_list(Edge_List *list);
void clear_edge_list(Edge_List *list);
void destroy_vertex_pointer_list(Vertex_Pointer_List *list);
void clear_vertex_pointer_list(Vertex_Pointer_List *list);
void vertex_list_push(Vertex_List *list, Vertex_Node *node);
void edge_list_push(Edge_List *list, Edge_Node *node);
void vertex_pointer_list_push(Vertex_Pointer_List *list, Vertex_Pointer_Node *node);
void vertex_list_pop(Vertex_List *list, Vertex_Node *node);
void edge_list_pop(Edge_List *list, Edge_Node *node);
void vertex_pointer_list_pop(Vertex_Pointer_List *list, Vertex_Pointer_Node *node);
void print_vertex_list(Vertex_List *list);
void print_edge_list(Edge_List *list);
void print_vertex_pointer_list(Vertex_Pointer_List *list);
Vertex_Pointer_Node *get_vertex_pointer_node(Vertex_Pointer_List *list, Vertex_Node *vertex_node);
Edge_Pointer_Node *new_edge_pointer_node();
Edge_Pointer_List *new_edge_pointer_list();
void destroy_edge_pointer_list(Edge_Pointer_List *list);
void clear_edge_pointer_list(Edge_Pointer_List *list);
void edge_pointer_list_push(Edge_Pointer_List *list, Edge_Pointer_Node *node);
void edge_pointer_list_pop(Edge_Pointer_List *list, Edge_Pointer_Node *node);
void print_edge_pointer_list(Edge_Pointer_List *list);