#pragma once

#include "data_types.h"

#include <stdlib.h>
#include <memory.h>

Dynamic_Array *new_dynamic_array();
void array_push(Dynamic_Array *dyn_array, Linked_List *linked_list);
void destroy_dynamic_array(Dynamic_Array *array);
void print_dynamic_array(Dynamic_Array *dyn_array);