#include "typedefs.h"
#include "debugmalloc.h"
#include <memory.h>
#include <stdio.h>

Array *new_array();
void destroy_array(Array *d_arr, MODES mode, bool destroy_data);
void array_push(Array *d_arr, void *item);
void array_insert(Array *d_arr, void *item, size_t index);
void array_delete(Array *d_arr, size_t index);
void print_array(Array *d_arr);