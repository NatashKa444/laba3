#ifndef SORTING_H
#define SORTING_H

#include "stack.h"
#include <time.h>

void insertion_sort_stack(Elem **Top);
void merge_sort_stack(Elem **Top);
void compare_sorting_methods();

void sort_file(const char *filename);

#endif