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

void read_from_file(Elem **Top, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        push(Top, num);
    }

    fclose(file);
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

// Обработка режима --file
void process_file_mode(const char *filename)
{
    printf("Режим работы с файлом: %s\n", filename);

    Elem *Top = NULL;
    read_from_file(&Top, filename);

    if (Top == NULL)
    {
        printf("Файл пуст или не содержит чисел!\n");
        return;
    }

    printf("Исходный ряд чисел: ");
    print_stack(Top);

    write_to_file(Top, "input.txt");
    printf("Исходный ряд записан в input.txt\n");

    clear_stack(&Top);
}