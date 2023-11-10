/**
 * @file typedefs.h
 * @author Szmoleniczki Ákos
 * @brief Ez a fájl a program által használt adattípusokat tartalmazza.
 * @version 0.1
 * @date 2023-11-09
 */

#pragma once

#include <stdlib.h>

/**
 * @brief A print_list függvényhez tartozó üzemmódok.
 * @see print_list 
 */
typedef enum PRINT_MODES {
    INT, VERTEX_DATA
} PRINT_MODES;

/**
 * @brief A gráf egy pontjához tartozó adatok 
 */
typedef struct Vertex_Data {
    unsigned int id;
} Vertex_Data;

/**
 * @brief Láncolt lista egy eleme. Eltárol egy mutatót az adattagjára és egyet a következő listaelemre.
 */
typedef struct List_Node {
    void *data;
    struct List_Node *next_node;
} List_Node;

/**
 * @brief Láncolt lista. Eltárol egy mutatót az első és utolsó elemére. 
 */
typedef struct List {
    List_Node *head_node;
    List_Node *tail_node;
} List;

/**
 * @brief Dinamikus tömb. Eltárolja a tömb méretét és egy void mutatókból álló tömböt, így akarmályien típusú elemeket tud tárolni.
 * 
 */
typedef struct Array {
    size_t size;
    void **array;
} Array;