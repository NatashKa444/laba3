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
void clear_stack(Elem **Top);

void write_to_file(Elem *Top, const char *filename);
void append_to_file(Elem *Top, const char *filename);
void read_from_file(char *filename);

#endif