#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Elem
{
    int inf;
    struct Elem *link;
} Elem;

void push(Elem **Top, int value);
int pop(Elem **Top);
void print_stack(Elem *Top);
int stack_size(Elem *Top);
void clear_stack(Elem **Top);

#endif