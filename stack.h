#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct Elem
{
    int data;
    struct Elem *next;
} Elem;

typedef struct
{
    Elem *top;
    int size;
} Stack;

Stack *createStack();
void push(Stack *stack, int data);
int pop(Stack *stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);
int getStackSize(Stack *stack);
void insertAtPosition(Stack *stack, int position, int data);
void deleteAtPosition(Stack *stack, int position);
void editAtPosition(Stack *stack, int position, int newData);

// void insertionSort(Stack* stack);
// Stack* mergeSort(Stack* stack);
// void measureSortTime(Stack* stack, const char* sortType, const char* filename);

// void saveStackToFile(Stack* stack, const char* filename);
// Stack* loadStackFromFile(const char* filename);
// void generateTestFiles();

void clearInputBuffer();
int askToContinue();

#endif