#include "sorting.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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

// Функция слияния двух отсортированных стеков
Elem *merge(Elem *left, Elem *right)
{
    Elem *result = NULL;
    Elem *temp_stack = NULL;

    // Сливаем пока оба стека не пусты
    while (left != NULL && right != NULL)
    {
        if (left->inf <= right->inf)
        {
            push(&temp_stack, left->inf);
            left = left->link;
        }
        else
        {
            push(&temp_stack, right->inf);
            right = right->link;
        }
    }

    // Добавляем оставшиеся элементы из левого стека
    while (left != NULL)
    {
        push(&temp_stack, left->inf);
        left = left->link;
    }

    // Добавляем оставшиеся элементы из правого стека
    while (right != NULL)
    {
        push(&temp_stack, right->inf);
        right = right->link;
    }

    // Разворачиваем временный стек чтобы получить правильный порядок
    while (temp_stack != NULL)
    {
        push(&result, pop(&temp_stack));
    }

    return result;
}

// Разделение стека на две части
void split_stack(Elem *Top, Elem **left, Elem **right)
{
    if (Top == NULL || Top->link == NULL)
    {
        *left = Top;
        *right = NULL;
        return;
    }

    // Используем метод "черепаха и заяц" для нахождения середины
    Elem *slow = Top;
    Elem *fast = Top->link;

    // fast двигается в 2 раза быстрее slow
    while (fast != NULL)
    {
        fast = fast->link;
        if (fast != NULL)
        {
            slow = slow->link;
            fast = fast->link;
        }
    }

    // slow указывает на середину
    *left = Top;
    *right = slow->link;
    slow->link = NULL; // Разрываем связь между половинами
}

// Сортировка слиянием на стеке (рекурсивная)
void merge_sort_stack(Elem **Top)
{
    if (*Top == NULL || (*Top)->link == NULL)
    {
        return; // Базовый случай: стек пуст или содержит один элемент
    }

    Elem *left = NULL;
    Elem *right = NULL;

    // Разделяем стек на две части
    split_stack(*Top, &left, &right);

    // Рекурсивно сортируем каждую часть
    merge_sort_stack(&left);
    merge_sort_stack(&right);

    // Сливаем отсортированные части
    *Top = merge(left, right);
}

// Сравнение методов сортировки
void compare_sorting_methods()
{
    setlocale(LC_ALL, "Russian");
    printf("\nСравнение методов сортировки:\n");
    printf("Размер | Вставками(с) | Слиянием(с)\n");
    printf("-----------------------------------\n");

    // для сохранения результатов
    FILE *results = fopen("results.txt", "w");
    if (results == NULL)
    {
        printf("Ошибка создания файла results.txt\n");
        return;
    }
    fprintf(results, "Size Insertion Merge\n");

    FILE *file = fopen("smallest.txt", "r"); // (1) 100 чисел
    if (file != NULL)
    {
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
        double time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", 100, time_insertion, time_merge);
        fprintf(results, "%d %.4f %.4f\n", 100, time_insertion, time_merge);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    file = fopen("small.txt", "r"); // (2) 500 чисел
    if (file != NULL)
    {
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
        double time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", 500, time_insertion, time_merge);
        fprintf(results, "%d %.4f %.4f\n", 500, time_insertion, time_merge);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    file = fopen("medium.txt", "r"); // (3) 1000 чисел
    if (file != NULL)
    {
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
        double time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", 1000, time_insertion, time_merge);
        fprintf(results, "%d %.4f %.4f\n", 1000, time_insertion, time_merge);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    file = fopen("big.txt", "r"); // (4) 5000 чисел
    if (file != NULL)
    {
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
        double time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", 5000, time_insertion, time_merge);
        fprintf(results, "%d %.4f %.4f\n", 5000, time_insertion, time_merge);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    file = fopen("biggest.txt", "r"); // (5) 10000 чисел
    if (file != NULL)
    {
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
        double time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", 10000, time_insertion, time_merge);
        fprintf(results, "%d %.4f %.4f\n", 10000, time_insertion, time_merge);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    fclose(results);

    printf("\nЗапускаем построение графика...\n");
    system("python graph.py");
}