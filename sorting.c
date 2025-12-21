#include "sorting.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>
const int COUNT_REPEATS = 50;

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

Elem *merge(Elem *left, Elem *right)
{
    Elem *result = NULL;
    Elem *temp_stack = NULL;

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

    // Оставшиеся элементы из левого стека
    while (left != NULL)
    {
        push(&temp_stack, left->inf);
        left = left->link;
    }

    // И из правого
    while (right != NULL)
    {
        push(&temp_stack, right->inf);
        right = right->link;
    }

    // Разворот временного стека для правильного порядка
    while (temp_stack != NULL)
    {
        push(&result, pop(&temp_stack));
    }
    return result;
}

void split_stack(Elem *Top, Elem **left, Elem **right)
{
    if (Top == NULL || Top->link == NULL)
    {
        *left = Top;
        *right = NULL;
        return;
    }

    Elem *slow = Top;
    Elem *fast = Top->link;
    while (fast != NULL)
    {
        fast = fast->link;
        if (fast != NULL)
        {
            slow = slow->link;
            fast = fast->link;
        }
    }
    *left = Top;
    *right = slow->link;
    slow->link = NULL; 
}

void merge_sort_stack(Elem **Top)
{
    if (*Top == NULL || (*Top)->link == NULL)
    {
        return;
    }

    Elem *left = NULL;
    Elem *right = NULL;

    split_stack(*Top, &left, &right);

    merge_sort_stack(&left);
    merge_sort_stack(&right);

    *Top = merge(left, right); 
}


void compare_sorting_methods()
{
    setlocale(LC_ALL, "Russian");
    FILE *check = fopen("results.txt", "r");
    if (check != NULL)
    {
        fclose(check);
        printf("\nПостроение графика...\n");
        system("python graph.py");
        return;
    }

    FILE *results = fopen("results.txt", "w");
    if (results == NULL)
    {
        printf("Ошибка создания файла results.txt\n");
        return;
    }
    fprintf(results, "Size Insertion Merge\n");
    
    // Измерение smallest.txt (50 чисел)
    double once_insertion = 0.0;
    double once_merge = 0.0;
    for (int repeat = 0; repeat < COUNT_REPEATS; repeat++)
    {
        FILE *file = fopen("smallest.txt", "r");
        if (file == NULL)
        {
            printf("Ошибка: не удалось открыть файл smallest.txt\n");
            return;
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
        once_insertion += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        once_merge += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        clear_stack(&stack1);
        clear_stack(&stack2);
        
    }
    double avg_insertion = once_insertion / COUNT_REPEATS;
    double avg_merge = once_merge / COUNT_REPEATS;
    fprintf(results, "50 %.6f %.6f\n", avg_insertion, avg_merge);
    
    // Измерение small.txt (100 чисел)
    once_insertion = 0.0;
    once_merge = 0.0;
    for (int repeat = 0; repeat < COUNT_REPEATS; repeat++)
    {
        FILE *file = fopen("small.txt", "r");
        if (file == NULL)
        {
            printf("Ошибка: не удалось открыть файл small.txt\n");
            return;
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
        once_insertion += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        once_merge += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        clear_stack(&stack1);
        clear_stack(&stack2);
        
    }
    
    avg_insertion = once_insertion / COUNT_REPEATS;
    avg_merge = once_merge / COUNT_REPEATS;
    fprintf(results, "100 %.6f %.6f\n", avg_insertion, avg_merge);
    
    // Измерение medium.txt (1000 чисел)
    once_insertion = 0.0;
    once_merge = 0.0;
    for (int repeat = 0; repeat < COUNT_REPEATS; repeat++)
    {
        FILE *file = fopen("medium.txt", "r");
        if (file == NULL)
        {
            printf("Ошибка: не удалось открыть файл medium.txt\n");
            return;
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
        once_insertion += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        once_merge += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        clear_stack(&stack1);
        clear_stack(&stack2);
        
    }
    
    avg_insertion = once_insertion / COUNT_REPEATS;
    avg_merge = once_merge / COUNT_REPEATS;
    fprintf(results, "500 %.6f %.6f\n", avg_insertion, avg_merge);
    
    // Измерение big.txt (5000 чисел)
    once_insertion = 0.0;
    once_merge = 0.0;
    for (int repeat = 0; repeat < COUNT_REPEATS; repeat++)
    {
        FILE *file = fopen("big.txt", "r");
        if (file == NULL)
        {
            printf("Ошибка: не удалось открыть файл big.txt\n");
            return;
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
        once_insertion += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        once_merge += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        clear_stack(&stack1);
        clear_stack(&stack2);
        
    }
    
    avg_insertion = once_insertion / COUNT_REPEATS;
    avg_merge = once_merge / COUNT_REPEATS;
    fprintf(results, "1000 %.6f %.6f\n", avg_insertion, avg_merge);
    
    // Измерение biggest.txt (2000 чисел)
    once_insertion = 0.0;
    once_merge = 0.0;
    for (int repeat = 0; repeat < COUNT_REPEATS; repeat++)
    {
        FILE *file = fopen("biggest.txt", "r");
        if (file == NULL)
        {
            printf("Ошибка: не удалось открыть файл biggest.txt\n");
            return;
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
        once_insertion += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        start = clock();
        merge_sort_stack(&stack2);
        end = clock();
        once_merge += ((double)(end - start)) / CLOCKS_PER_SEC;
        
        clear_stack(&stack1);
        clear_stack(&stack2);
    }

    avg_insertion = once_insertion / COUNT_REPEATS;
    avg_merge = once_merge / COUNT_REPEATS;
    fprintf(results, "2000 %.6f %.6f\n", avg_insertion, avg_merge);

    fclose(results);
    printf("Результаты сохранены в файл results.txt\n");
    printf("Построение графика...\n");
    system("python graph.py");
}