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
        read_from_file("input.txt");
        read_from_file("sorted.txt");
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

    while (getchar() != '\n')
        ;

    if (Top == NULL)
    {
        printf("Вы не ввели числа! Используются тестовые данные.\n");
        return -1;
    }

    printf("Создан стек: ");
    print_stack(Top);
    write_to_file(Top, "input.txt");

    while (choice != 4)
    {
        printf("1. Сортировка прямым включением\n");
        printf("2. Сортировка слиянием\n");
        printf("3. Сравнение методов сортировки\n");
        printf("4. Выход\n");
        printf("Выберите опцию: ");

        scanf("%d", &choice);
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            printf("До сортировки: ");
            print_stack(Top);
            insertion_sort_stack(&Top);
            printf("После сортировки: ");
            print_stack(Top);
            write_to_file(Top, "sorted.txt");
            break;

        case 2:
            printf("До сортировки: ");
            print_stack(Top);
            merge_sort_stack(&Top);
            printf("После сортировки: ");
            print_stack(Top);
            write_to_file(Top, "sorted.txt");
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
    }

    clear_stack(&Top);
    return 0;
}