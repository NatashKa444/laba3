#include "stack.h"

// Добавление элемента в стек
void push(Elem **Top, int value)
{
    Elem *p = (Elem *)malloc(sizeof(Elem));
    p->inf = value;
    p->link = *Top;
    *Top = p;
}

// Удаление элемента из стека
int pop(Elem **Top)
{
    if (*Top == NULL)
        return -1;

    int val = (*Top)->inf;
    Elem *p = *Top;
    *Top = (*Top)->link;
    free(p);
    return val;
}

// Печать стека
void print_stack(Elem *Top)
{
    Elem *current = Top;
    while (current != NULL)
    {
        printf("%d ", current->inf);
        current = current->link;
    }
    printf("\n");
}

// Размер стека
int stack_size(Elem *Top)
{
    int count = 0;
    Elem *current = Top;
    while (current != NULL)
    {
        count++;
        current = current->link;
    }
    return count;
}

// Очистка стека
void clear_stack(Elem **Top)
{
    while (*Top != NULL)
    {
        pop(Top);
    }
}