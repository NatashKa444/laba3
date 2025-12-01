#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "stack.h"
#include "sorting.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    Elem *top = NULL;
    int choice;
    printf("Введите числа через пробел: ");
    int num;
    while (scanf("%d", &num) == 1)
    {
        push(&top, num);
    }
    while (getchar() != '\n')
        ;
    printf("Создан стек из %d элементов: ", stack_size(top));
    print_stack(top);

    // Основной цикл программы
    do
    {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Сортировка прямым включением\n");
        printf("2. Сортировка слиянием\n");
        printf("3. Сравнить методы сортировки\n");
        printf("4. Выход\n");
        printf("Выберите: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("До сортировки: ");
            print_stack(top);
            insertion_sort_stack(&top);
            printf("После сортировки: ");
            print_stack(top);
            break;

        case 2:
            printf("До сортировки: ");
            print_stack(top);
            merge_sort_stack(&top);
            printf("После сортировки: ");
            print_stack(top);
            break;

        case 3:
            compare_sorting_methods();
            break;

        case 4:
            printf("Выход\n");
            break;

        default:
            printf("Неверный выбор!\n");
        }

    } while (choice != 4);

    clear_stack(&top);
    return 0;
}