/**
 * @file dynamic_array.c
 * @author Szmoleniczki Ákos
 * @brief Ez a fájl a dinamikus tömbök kezeléséhez szükséges függvényeket tartalmazza.
 * @version 0.1
 * @date 2023-11-10
 */

#include "dynamic_array.h"
#include "linked_list.h"

/**
 * @brief Létrehoz egy új dinamikus tömböt, nulla hosszúsággal és egy üres tömbbel, majd visszaadja a memóriacímét. Nem szabadít fel memóriát!
 * 
 * @return Array* A létrehozott tömb memóriacíme.
 */
Array *new_array() {
    Array *d_arr = (Array *) malloc(sizeof(Array));
    d_arr->size = 0;
    void **arr = (void **) malloc(d_arr->size * sizeof(void *));
    d_arr->array = arr;

    return d_arr;
}

/**
 * @brief Felszabadítja a megadott dinamikus tömböt és annak összes elemét.
 * 
 * @param d_arr A felszabadítandó dianmikus tömb.
 */
void destroy_array(Array *d_arr, MODES mode, bool destroy_data) {
    for (size_t i = 0; i < d_arr->size; i++) {
        switch (mode) {
            case LINKED_LIST:
                destroy_list(d_arr->array[i], destroy_data);
                break;
            default:
                free(d_arr->array[i]);
                break;
        }
    }

    free(d_arr->array);
    d_arr->array = NULL;
    free(d_arr);
    d_arr = NULL;
}

/**
 * @brief Hozzáad egy elemet a dinamikus tömb végéhez.
 * 
 * @param d_arr A dinamikus tömb, amihez hozzáadja az elemet.
 * @param item Az elem, amit hozzáad a tömbhöz.
 */
void array_push(Array *d_arr, void *item) {
    size_t old_size = d_arr->size++;
    void **new_arr = (void **) malloc(d_arr->size * sizeof(void *));

    for (size_t i = 0; i < old_size; i++) {
        new_arr[i] = d_arr->array[i];
    }

    new_arr[old_size] = item;

    free(d_arr->array);    
    d_arr->array = new_arr;
}

/**
 * @brief Beszúr egy elemet a megadott dinamikus tömbbe a megadott helyen.
 * @details Ha a megadott index nagyobb, mint a tömb mérete, akkor azt a tömb méretével megegyezőnek veszi (a tömb végére szúr be).
 * 
 * @param d_arr A dinamikus tömb, amibe beszúrja az elemet.
 * @param item Az elem, amit beszúr a tömbbe.
 * @param index Az index (hely), ahova beszúrja az elemet.
 */
void array_insert(Array *d_arr, void *item, size_t index) {
    size_t old_size = d_arr->size++;
    void **new_arr = (void **) malloc(d_arr->size * sizeof(void *));
    size_t i = 0;

    if (index > old_size) index = old_size;

    for (i; i < index; i++) {
        new_arr[i] = d_arr->array[i];
    }

    new_arr[i++] = item;

    for (i; i < d_arr->size; i++) {
        new_arr[i] = d_arr->array[i - 1];
    }

    free(d_arr->array);    
    d_arr->array = new_arr;
}

/**
 * @brief Kitörli a tömb megadott indexének helyén álló elemet a tömbből.
 * @details Ha a megadott index nagyobb, mint a tömb mérete, akkor azt a tömb méretével megegyezőnek veszi. Ha a tömb már amúgy is üres, akkor nem csinál semmit.
 * 
 * @param d_arr A dinamikus tömb, amiből töröl.
 * @param index Az index (hely), ahonnan töröl.
 */
void array_delete(Array *d_arr, size_t index) {
    if (d_arr->size == 0) return;

    size_t old_size = d_arr->size--;
    void **new_arr = (void **) malloc(d_arr->size * sizeof(void *));
    size_t i = 0;

    if (index > old_size) index = old_size;

    for (i; i < index; i++) {
        new_arr[i] = d_arr->array[i];
    }

    free(d_arr->array[i++]);

    for (i; i < old_size; i++) {
        new_arr[i - 1] = d_arr->array[i];
    }

    free(d_arr->array);    
    d_arr->array = new_arr;
}

/**
 * @todo Dokumentáció
 * @brief 
 * 
 * @param d_arr 
 */
void print_array(Array *d_arr) {
    for (size_t i = 0; i < d_arr->size; i++) {
        //printf("niga\n");
        printf("%d%s", *((int *) d_arr->array[i]), i == d_arr->size - 1 ? "\n" : ", ");
    }
}

// int main() {
//     Array *arr = new_array();

//     int *i0 = (int *) malloc(sizeof(int));
//     *i0 = 69;
//     int *i1 = (int *) malloc(sizeof(int));
//     *i1 = 420;
//     int *i2 = (int *) malloc(sizeof(int));
//     *i2 = 123;

//     array_push(arr, i0);
//     array_push(arr, i1);
//     array_insert(arr, i2, 1);
//     array_delete(arr, 1);

//     print_array(arr);

//     destroy_array(arr);
// }