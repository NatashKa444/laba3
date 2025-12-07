#include "sorting.h"
#include <stdlib.h>

// Сортировка прямым включением
void insertion_sort_stack(Elem **Top)
{
    if (*Top == NULL || (*Top)->link == NULL)
        return;

    Elem *sorted = NULL;

    while (*Top != NULL)
    {
        int current = pop(Top);

        while (sorted != NULL && sorted->inf > current)
        {
            push(Top, pop(&sorted));
        }

        push(&sorted, current);
    }

    while (sorted != NULL)
    {
        push(Top, pop(&sorted));
    }
}

// Сортировка слиянием (упрощенная)
void merge_sort_stack(Elem **Top)
{
    if (*Top == NULL || (*Top)->link == NULL)
        return;

    Elem *slow = *Top;
    Elem *fast = (*Top)->link;

    while (fast != NULL && fast->link != NULL)
    {
        slow = slow->link;
        fast = fast->link->link;
    }

    Elem *left = *Top;
    Elem *right = slow->link;
    slow->link = NULL;

    merge_sort_stack(&left);
    merge_sort_stack(&right);

    Elem *result = NULL;
    Elem **tail = &result;

    while (left != NULL && right != NULL)
    {
        if (left->inf <= right->inf)
        {
            *tail = left;
            left = left->link;
        }
        else
        {
            *tail = right;
            right = right->link;
        }
        tail = &((*tail)->link);
    }

    *tail = (left != NULL) ? left : right;
    *Top = result;
}

// Сравнение методов сортировки
void compare_sorting_methods()
{
    printf("\nСравнение методов сортировки:\n");
    printf("Размер | Вставками(с) | Слиянием(с)\n");
    printf("-----------------------------------\n");

    char *files[] = {"small.txt", "medium.txt", "large.txt"};
    int sizes[] = {10, 100, 1000};

    FILE *results = fopen("results.txt", "w");
    fprintf(results, "Size Insertion Merge\n");

    for (int i = 0; i < 3; i++)
    {
        FILE *file = fopen(files[i], "r");
        if (file == NULL)
        {
            printf("Ошибка открытия файла %s\n", files[i]);
            continue;
        }

        Elem *stack1 = NULL;
        Elem *stack2 = NULL;
        int num;

        while (fscanf(file, "%d", &num) == 1)
        {
            push(&stack1, num);
            push(&stack2, num);
        }
        fclose(file);

        clock_t start = clock();
        insertion_sort_stack(&stack1);
        clock_t end = clock();
        double time1 = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time2 = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", sizes[i], time1, time2);

        fprintf(results, "%d %.4f %.4f\n", sizes[i], time1, time2);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    fclose(results);

    printf("\nЗапускаем построение графика...\n");
    system("python graph.py");
}