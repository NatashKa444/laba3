#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "stack.h"
#include "sorting.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    // Запуск с аргументом --file filename.txt
    if (argc == 3 && strcmp(argv[1], "--file") == 0)
    {
        printf("Режим работы с файлом: %s\n", argv[2]);
        printf("Введите числа через пробел (для завершения введите любой не-число): ");
        int num;
        Elem *original_stack = NULL;
        while (scanf("%d", &num) == 1)
        {
            push(&original_stack, num);
        }
        while (getchar() != '\n')
            ;
        if (original_stack == NULL)
        {
            return 0;
        }
        printf("Введенный ряд чисел: ");
        print_stack(original_stack);

        write_to_file(original_stack, argv[2]);
        printf("Исходные данные записаны в %s\n", argv[2]);

        insertion_sort_stack(&original_stack);
        printf("Отсортированный ряд: ");
        print_stack(original_stack);
        append_to_file(original_stack, argv[2]);
        printf("Отсортированные данные дописаны в %s\n", argv[2]);

        clear_stack(&original_stack);
        return 0;
    }

    // Обычный режим работы
    Elem *Top = NULL;
    int choice;

    printf("Введите числа через пробел (для завершения введите любой не-число): ");

    int num;
    while (scanf("%d", &num) == 1)
    {
        push(&Top, num);
    }

    // Очистка буфера
    while (getchar() != '\n')
        ;

    // Если ничего не ввели
    if (Top == NULL)
    {
        printf("Вы не ввели числа! Используются тестовые данные.\n");
        push(&Top, 5);
        push(&Top, 2);
        push(&Top, 8);
        push(&Top, 1);
        push(&Top, 9);
    }

    printf("Создан стек: ");
    print_stack(Top);

    // Основной цикл
    do
    {
        // Меню прямо в main (без функции)
        printf("\n=== МЕНЮ РАБОТЫ СО СТЕКОМ ===\n");
        printf("1. Сортировка прямым включением\n");
        printf("2. Сортировка слиянием\n");
        printf("3. Сравнение методов сортировки\n");
        printf("4. Выход\n");
        printf("Выберите опцию: ");

        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Очистка буфера

        switch (choice)
        {
        case 1:
            printf("До сортировки: ");
            print_stack(Top);
            insertion_sort_stack(&Top);
            printf("После сортировки: ");
            print_stack(Top);
            break;

        case 2:
            printf("До сортировки: ");
            print_stack(Top);
            merge_sort_stack(&Top);
            printf("После сортировки: ");
            print_stack(Top);
            break;

        case 3:
            compare_sorting_methods();
            break;

        case 4:
            printf("Выход из программы...\n");
            break;

        default:
            printf("Неверный выбор! Введите 1-4.\n");
        }

    } while (choice != 4);

    clear_stack(&Top);
    return 0;
}