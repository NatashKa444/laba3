#include "sorting.h"
#include <stdlib.h> // для system()

// Сортировка прямым включением (простая)
void insertion_sort_stack(Elem **top)
{
    if (*top == NULL || (*top)->next == NULL)
        return;

    Elem *sorted = NULL; // Второй стек для сортировки

    while (*top != NULL)
    {
        int current = pop(top); // Берем элемент из исходного стека

        // Находим правильное место в отсортированном стеке
        while (sorted != NULL && sorted->data > current)
        {
            push(top, pop(&sorted));
        }

        push(&sorted, current); // Добавляем в отсортированный стек
    }

    // Возвращаем отсортированные элементы обратно
    while (sorted != NULL)
    {
        push(top, pop(&sorted));
    }
}

// Сортировка слиянием (упрощенная)
void merge_sort_stack(Elem **top)
{
    if (*top == NULL || (*top)->next == NULL)
        return;

    // Разделяем стек на две части
    Elem *slow = *top;
    Elem *fast = (*top)->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Elem *left = *top;
    Elem *right = slow->next;
    slow->next = NULL;

    // Сортируем каждую часть
    merge_sort_stack(&left);
    merge_sort_stack(&right);

    // Сливаем отсортированные части
    Elem *result = NULL;
    Elem **tail = &result;

    while (left != NULL && right != NULL)
    {
        if (left->data <= right->data)
        {
            *tail = left;
            left = left->next;
        }
        else
        {
            *tail = right;
            right = right->next;
        }
        tail = &((*tail)->next);
    }

    *tail = (left != NULL) ? left : right;
    *top = result;
}
// Сравнение методов сортировки
void compare_sorting_methods()
{
    printf("\nСравнение методов сортировки:\n");
    printf("Размер | Вставками(с) | Слиянием(с)\n");
    printf("-----------------------------------\n");

    // Используем готовые тестовые файлы
    char *files[] = {"small.txt", "medium.txt", "large.txt"};
    int sizes[] = {10, 100, 1000};

    // ИСПРАВЛЕНО: Открываем файл для записи (перезаписываем)
    FILE *results = fopen("results.txt", "w");
    if (results == NULL)
    {
        printf("Ошибка создания файла results.txt\n");
        return;
    }

    // Записываем заголовок
    fprintf(results, "Size Insertion Merge\n");

    for (int i = 0; i < 3; i++)
    {
        // Читаем числа из готового файла
        FILE *file = fopen(files[i], "r");
        if (file == NULL)
        {
            printf("Ошибка открытия файла %s\n", files[i]);
            fclose(results);
            return; // тренировочный редактор
        }

        // Создаем два одинаковых стека для тестирования
        Elem *stack1 = NULL;
        Elem *stack2 = NULL;
        int num;

        // Читаем все числа из готового файла
        while (fscanf(file, "%d", &num) == 1)
        {
            push(&stack1, num);
            push(&stack2, num);
        }
        fclose(file);

        // Тестируем сортировку вставками
        clock_t start = clock();
        insertion_sort_stack(&stack1);
        clock_t end = clock();
        double time1 = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Тестируем сортировку слиянием
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