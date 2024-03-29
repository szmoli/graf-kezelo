#include "saves.h"

char *get_date_time_str() {
    time_t raw_time;
    time(&raw_time);
    struct tm *local_time = localtime(&raw_time);
    size_t buffer_size = 25;
    char *buffer = (char *) malloc((buffer_size + 1) * sizeof(char));

    while (strftime(buffer, buffer_size, "%Y-%m-%d_%H%M%S", local_time) == 0) {
        free(buffer);
        buffer_size *= 2;
        buffer = (char *) malloc((buffer_size + 1) * sizeof(char));
    }

    return buffer;
}

char *get_save_file_path(char *saves_dir, char *extension, char *time_str) {
    char *save_path = (char *) malloc((strlen(saves_dir) + strlen(time_str) + strlen(extension) + 1) * sizeof(char));

    strcpy(save_path, saves_dir);
    strcat(save_path, time_str);
    strcat(save_path, extension);

    return save_path;
}

void check_and_make_saves_dir(char *saves_dir) {
    struct stat st;

    if (stat(saves_dir, &st) == -1) {
        _mkdir(saves_dir); 
    }
}

void save_vertices_and_selection(Vertex_List *list, FILE *save_file) {
    Vertex_Node *iterator = list->head;

    while (iterator != NULL) {
        Vertex_Data vd = iterator->vertex_data;

        // id, selected, red, green, blue, alpha, radius
        fprintf(save_file, "%d,%d,%d,%d,%d,%d,%d\n", vd.id, vd.selected, vd.red, vd.green, vd.blue, vd.alpha, vd.radius);

        iterator = iterator->next_node;
    }
}

void save_edges(Edge_List *list, FILE *save_file) {
    Edge_Node *iterator = list->head;

    while (iterator != NULL) {
        Edge edge = iterator->edge;
        Vertex_Data vd_to = edge.to->vertex_data;
        Vertex_Data vd_from = edge.from->vertex_data;

        // from, to, red, green, blue, alpha, width
        fprintf(save_file, "%d,%d,%d,%d,%d,%d,%d\n", vd_from.id, vd_to.id, edge.red, edge.green, edge.blue, edge.alpha, edge.width);

        iterator = iterator->next_node;
    }
}

void save_graph(Vertex_List *vertices, Edge_List *edges, char *vertices_save_path, char *edges_save_path, char *graph_save_path) {
    FILE *vertices_save_file = fopen(vertices_save_path, "w");
    FILE *edges_save_file = fopen(edges_save_path, "w");
    FILE *graph_save_file = fopen(graph_save_path, "w");

    save_vertices_and_selection(vertices, vertices_save_file);
    save_edges(edges, edges_save_file);

    fclose(vertices_save_file);
    fclose(edges_save_file);
    fclose(graph_save_file);
}

bool is_valid_graph_file(char *file_path, char *graph_file_estension) {
    char *last = strrchr(file_path, '.');
    
    return (strcmp(last, graph_file_estension) == 0);
}

char *get_date_time_str_from_file_path(char *file_path) {
    char *last = strrchr(file_path, '\\');
    char *token = strtok(last + 1, ".");
    return token;
}

void load_vertices_and_selection(Vertex_List *vertices, Vertex_Pointer_List *selection, FILE *file, int *max_id) {
    bool reading = true;
    
    while (reading) {
        Vertex_Node *node = new_vertex_node();
        Vertex_Data *vd = &(node->vertex_data);

        int read_count = fscanf(file, "%d,%d,%d,%d,%d,%d,%d\n", &vd->id, &vd->selected, &vd->red, &vd->green, &vd->blue, &vd->alpha, &vd->radius);
        if (read_count == 7) {
            if (*max_id < vd->id) *max_id = vd->id + 1;

            vertex_list_push(vertices, node);

            if (vd->selected) {
                Vertex_Pointer_Node *selection_node = new_vertex_pointer_node();
                selection_node->vertex_node = node;
                vertex_pointer_list_push(selection, selection_node);
            }

        } else if (read_count == EOF) {
            reading = false;
            free(node);
        }
    }
}

void load_edges(Edge_List *edges, Vertex_List *vertices, FILE *file) {
    bool reading = true;
    
    while (reading) {
        Edge_Node *node = new_edge_node();
        Edge *edge = &(node->edge);
        int from_id;        
        int to_id;        

        int read_count = fscanf(file, "%d,%d,%d,%d,%d,%d,%d\n", &from_id, &to_id, &edge->red, &edge->green, &edge->blue, &edge->alpha, &edge->width);

        if (read_count == 7) {
            Vertex_Node *from = get_vertex_node_by_id(vertices, from_id);
            Vertex_Node *to = get_vertex_node_by_id(vertices, to_id);

            if (from != NULL && to != NULL) {
                node->edge.from = from;
                node->edge.to = to;
                edge_list_push(edges, node);

            } else {
                free(node);
            }

        } else if (read_count == EOF) {
            reading = false;
            free(node);
        }
    }
}

void load_graph(Vertex_List *vertices, Edge_List *edges, Vertex_Pointer_List *selection, char *vertices_save_path, char *edges_save_path, int *max_id) {
    FILE *vertices_save_file = fopen(vertices_save_path, "r");
    FILE *edges_save_file = fopen(edges_save_path, "r");

    load_vertices_and_selection(vertices, selection, vertices_save_file, max_id);
    load_edges(edges, vertices, edges_save_file);
    
    fclose(vertices_save_file);
    fclose(edges_save_file);
}