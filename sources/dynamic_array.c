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
    // dyn_array->array = (Linked_List **) realloc(dyn_array->array, dyn_array->size * sizeof(Linked_List **));
    // dyn_array->array[dyn_array->size - 1] = linked_list;
    
    Linked_List **new_array = (Linked_List **) malloc(dyn_array->size * sizeof(Linked_List **));

    for (size_t i = 0; i < dyn_array->size - 1; i++) {
        printf("i: [%d] ", i);
        print_linked_list(dyn_array->array[i]);
        new_array[i] = dyn_array->array[i];
    }

    printf("kint: ");
    print_linked_list(linked_list);
    new_array[dyn_array->size - 1] = linked_list;

    free(dyn_array->array);
    dyn_array->array = new_array; 

    printf("vege\n");
}

void destroy_dynamic_array(Dynamic_Array *dyn_array) {
    for (size_t i = 0; i < dyn_array->size; i++) {
        printf("nigger: %d\n", i);
        free_linked_list(dyn_array->array[i]);
    }

    free(dyn_array->array);
    free(dyn_array);
    dyn_array = NULL;
}

void print_dynamic_array(Dynamic_Array *dyn_array) {
    for (size_t i = 0; i < dyn_array->size; i++) {
        print_linked_list(dyn_array->array[i]);
    }
}