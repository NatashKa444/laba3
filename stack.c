#include "stack.h"

void push(Elem **Top, int value)
{
    Elem *p = (Elem *)malloc(sizeof(Elem));
    p->inf = value;
    p->link = *Top;
    *Top = p;
}

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

void clear_stack(Elem **Top)
{
    while (*Top != NULL)
    {
        pop(Top);
    }
}

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

void write_to_file(Elem *Top, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Ошибка создания файла %s\n", filename);
        return;
    }

    Elem *current = Top;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->inf);
        current = current->link;
    }

    fclose(file);
}

void append_to_file(Elem *Top, const char *filename)
{
    FILE *file = fopen(filename, "a"); // Открываем для дописывания
    if (file == NULL)
    {
        printf("Ошибка открытия файла %s для дописывания\n", filename);
        return;
    }

    fprintf(file, "\n");
    Elem *current = Top;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->inf);
        current = current->link;
    }

    fclose(file);
}
