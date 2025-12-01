#ifndef SORTING_H
#define SORTING_H

#include "stack.h"
#include <time.h>

// Функции сортировки
void insertion_sort_stack(Elem **top); // Сортировка прямым включением
void merge_sort_stack(Elem **top);     // Сортировка слиянием
void compare_sorting_methods();        // Сравнение методов

#endif