#pragma once

#include <stdlib.h>
#include <memory.h>

struct Linked_List;

typedef struct Dynamic_Array {
    size_t size;
    struct Linked_List** array;
} Dynamic_Array;

extern Dynamic_Array *adjacency_array;

Dynamic_Array *new_dynamic_array();
void array_push(Dynamic_Array *dyn_array, Linked_List *linked_list);
void destroy_dynamic_array(Dynamic_Array *array);
void print_dynamic_array(Dynamic_Array *dyn_array);