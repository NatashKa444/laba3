#include "sorting.h"
#include <stdlib.h>
#include <string.h>

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

// Функция сортировки файла (п.2 задания) - БЕЗ МАССИВОВ
void sort_file(const char *filename)
{
    printf("\nСортировка файла %s:\n", filename);

    // Читаем числа из файла в стек
    Elem *Top = NULL;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        push(&Top, num);
    }
    fclose(file);

    if (Top == NULL)
    {
        printf("Файл пуст!\n");
        return;
    }

    // Сортируем стек методом прямого включения
    printf("Сортировка прямым включением...\n");
    insertion_sort_stack(&Top);

    // Создаем имя для выходного файла (без массива)
    // Просто используем фиксированное имя как в задании
    const char *output_filename = "output.txt";

    // Сохраняем отсортированный стек в файл
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        printf("Ошибка создания файла %s\n", output_filename);
        clear_stack(&Top);
        return;
    }

    Elem *current = Top;
    while (current != NULL)
    {
        fprintf(output_file, "%d ", current->inf);
        current = current->link;
    }
    fclose(output_file);

    printf("Отсортированный ряд записан в %s\n", output_filename);

    clear_stack(&Top);
}

// Сравнение методов сортировки - БЕЗ МАССИВОВ
void compare_sorting_methods()
{
    printf("\nСравнение методов сортировки:\n");
    printf("Размер | Вставками(с) | Слиянием(с)\n");
    printf("-----------------------------------\n");

    // Без массивов - тестируем файлы по отдельности
    FILE *results = fopen("results.txt", "w");
    if (results == NULL)
    {
        printf("Ошибка создания файла results.txt\n");
        return;
    }
    fprintf(results, "Size Insertion Merge\n");

    // Тестируем small.txt (10 чисел)
    FILE *file1 = fopen("small.txt", "r");
    if (file1 != NULL)
    {
        Elem *stack1 = NULL;
        Elem *stack2 = NULL;
        int num;

        while (fscanf(file1, "%d", &num) == 1)
        {
            push(&stack1, num);
            push(&stack2, num);
        }
        fclose(file1);

        clock_t start = clock();
        insertion_sort_stack(&stack1);
        clock_t end = clock();
        double time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        double time_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%6d | %12.4f | %10.4f\n", 10, time_insertion, time_merge);
        fprintf(results, "%d %.4f %.4f\n", 10, time_insertion, time_merge);

        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    // Тестируем medium.txt (100 чисел)
    FILE *file2 = fopen("medium.txt", "r");
    if (file2 != NULL)
    {
        Elem *stack1 = NULL;
        Elem *stack2 = NULL;
        int num;

        while (fscanf(file2, "%d", &num) == 1)
        {
            push(&stack1, num);
            push(&stack2, num);
        }
        fclose(file2);

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

    // Тестируем large.txt (1000 чисел)
    FILE *file3 = fopen("large.txt", "r");
    if (file3 != NULL)
    {
        Elem *stack1 = NULL;
        Elem *stack2 = NULL;
        int num;

        while (fscanf(file3, "%d", &num) == 1)
        {
            push(&stack1, num);
            push(&stack2, num);
        }
        fclose(file3);

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

    fclose(results);

    printf("\nЗапускаем построение графика...\n");
    system("python graph.py");
}