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

void read_from_file(Elem **Top, const char *filename);
void write_to_file(Elem *Top, const char *filename);
void process_file_mode(const char *filename);

#endif