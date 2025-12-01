#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Структура элемента стека с информационным и указательным полями
typedef struct elem
{
    int data;           // Информационное поле - хранит данные
    struct elem *next; // Указательное поле - ссылка на следующий элемент
} Elem;

// Структура стека
typedef struct
{
    Elem *top; // Указатель на вершину стека
    int size;  // Количество элементов в стеке
} Stack;

// Базовые операции стека
Stack *createStack();
void push(Stack *stack, int data);
int pop(Stack *stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);

// Сортировки
void insertionSort(Stack *stack);
Stack *mergeSort(Stack *stack);

// Работа с файлами
void saveStackToFile(Stack *stack, const char *filename);
Stack *loadStackFromFile(const char *filename);
void generateTestFile(int size, const char *filename);

// Сравнение сортировок
void compareSorts();

#endif