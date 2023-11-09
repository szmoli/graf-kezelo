/**
 * @file main.c
 * @author Szmoleniczki Ákos
 * @brief Gráfkezelő program
 * @version 0.1
 * @date 2023-11-09
 */

#include "debugmalloc.h"
#include "typedefs.h"
#include "linked_list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
    /**
     * @var unsigned int id
     * @brief A gráfpont azonosító.
     * @details Minden pontnak egyedi azonosítója van. Az azonosító mindig egyel növekszik, amikor egy új pontot hozunk létre, így gyakorlatilag a létrehozható pontjainknak felső határa 4294967295, azaz az unsigned int felső határa. 
     */
    unsigned int id = 0;

    /**
     * @var Linked_List *vertexes
     * @brief Lista az összes létező gráfpontról.
     * @details Amikor egy új pontot hozunk létre, azt ebben a listában tartjuk nyilván. Ha a felhasználó kitöröl egy pontot, az a listából is törlődik. A gráfot tároló adatstruktúra ennek a listának a tárolt pontjaira mutat, ha kitörlünk egy pontot, akkor azt a gráf adatstruktúrájából is kitöröljük.
     */
    Linked_List *vertexes = new_list();

    print_list(vertexes, VERTEX_DATA);

    destroy_list(vertexes);
    
    return 0;
}