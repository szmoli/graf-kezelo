/**
 * @file typedefs.h
 * @author Szmoleniczki Ákos
 * @brief Ez a fájl a program által használt adattípusokat tartalmazza.
 * @version 0.1
 * @date 2023-11-09
 */

#pragma once

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief 2D pont
 */
typedef struct Point {
    int x; //! X koordináta
    int y; //! Y koordináta
} Point;

/**
 * @brief A függvényekhez tartozó üzemmódok.
 */
typedef enum MODES {
    VERTEX_DATA, VERTEX_DATA_POINTER, LINKED_LIST
} MODES;

/**
 * @brief A gráf egy pontjához tartozó adatok 
 */
typedef struct Vertex_Data {
    unsigned int id; //! Vertex ID
    Point *center; //! Vertex középpont
    bool selected; //! Ki van-e választva?
} Vertex_Data;

/**
 * @brief Láncolt lista egy eleme. Eltárol egy mutatót az adattagjára és egyet a következő listaelemre.
 */
typedef struct Node {
    void *data; //! Listaelem adattagja
    struct Node *next_node; //! Következő listaelem
} Node;

/**
 * @brief Láncolt lista. Eltárol egy mutatót az első és utolsó elemére. 
 */
typedef struct List {
    size_t size; //! Lista hossza
    Node *head_node; //! Lista első eleme
    Node *tail_node; //! Lista utolsó eleme
} List;

/**
 * @brief Dinamikus tömb. Eltárolja a tömb méretét és egy void mutatókból álló tömböt, így akarmályien típusú elemeket tud tárolni.
 * 
 */
typedef struct Array {
    size_t size; //! Tömb mérete
    void **array; //! Maga a tömb
} Array;