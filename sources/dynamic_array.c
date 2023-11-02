#include "dynamic_array.h"

Dynamic_Array *new_dynamic_array() {
    Dynamic_Array *new_array = (Dynamic_Array *) malloc(sizeof(Dynamic_Array));

    new_array->size = 0;
    new_array->array = (Linked_List **) malloc(new_array->size * sizeof(Linked_List **));

    return new_array;
}

/*
    TODO: hibakezelés
*/
void array_push(Dynamic_Array *dyn_array, Linked_List *linked_list) {
    dyn_array->size++;    
    Linked_List **new_array = (Linked_List **) malloc(dyn_array->size * sizeof(Linked_List **));

    for (size_t i = 0; i < dyn_array->size - 1; i++) {
        // printf("i: [%d]\n", i);
        // print_linked_list(dyn_array->array[i]);
        new_array[i] = dyn_array->array[i];
    }

    // printf("kint:\n");
    // print_linked_list(linked_list);
    new_array[dyn_array->size - 1] = linked_list;

    free(dyn_array->array);
    dyn_array->array = new_array; 

    // printf("vege\n");
}

void array_pop(Dynamic_Array *dyn_array, int index) {
    size_t i = 0;
    size_t old_size = dyn_array->size;
    dyn_array->size--;
    Linked_List **new_array = (Linked_List **) malloc(dyn_array->size * sizeof(Linked_List **));

    for (i; i < index; i++) {
        new_array[i] = dyn_array->array[i];
    }
    
    i++;

    for (i; i < old_size; i++) {
        new_array[i - 1] = dyn_array->array[i];
    }

    free(dyn_array->array);
    dyn_array->array = new_array; 
}

void destroy_dynamic_array(Dynamic_Array *dyn_array) {
    for (size_t i = 0; i < dyn_array->size; i++) {
        //print_linked_list(dyn_array->array[i]);
        destroy_linked_list(dyn_array->array[i]);
    }

    free(dyn_array->array);
    free(dyn_array);
    dyn_array = NULL;
}

void print_dynamic_array(Dynamic_Array *dyn_array) {
    for (size_t i = 0; i < dyn_array->size; i++) {
        print_linked_list(dyn_array->array[i]);
        printf("kitepem a hajam\n");
    }
}