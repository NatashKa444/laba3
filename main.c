#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "stack.h"
#include "sorting.h"

// Функция для ввода чисел и создания стека
void input_numbers(Elem **top)
{
    printf("Введите числа через пробел: ");

    char input[1000];
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token != NULL)
    {
        int num = atoi(token);
        push(top, num);
        token = strtok(NULL, " ");
    }
}

// Обработка аргументов командной строки
void handle_command_line_args(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "--file") == 0)
    {
        printf("Режим работы с файлом: %s\n", argv[2]);

        Elem *top = NULL;

        // Читаем числа из файла
        FILE *file = fopen(argv[2], "r");
        if (file == NULL)
        {
            printf("Ошибка открытия файла %s\n", argv[2]);
            return;
        }

        int num;
        while (fscanf(file, "%d", &num) == 1)
        {
            push(&top, num);
        }
        fclose(file);

        printf("Исходный стек: ");
        print_stack(top);

        // Сортируем копию стека
        Elem *sorted = copy_stack(top);
        insertion_sort_stack(&sorted);

        printf("Отсортированный стек: ");
        print_stack(sorted);

        // Записываем в файлы
        write_stack_to_file(top, "original.txt");
        write_stack_to_file(sorted, "sorted.txt");

        printf("Исходные данные записаны в 'original.txt'\n");
        printf("Отсортированные данные записаны в 'sorted.txt'\n");

        clear_stack(&top);
        clear_stack(&sorted);
    }
}

// Основное меню
void show_menu()
{
    printf("\n=== МЕНЮ РАБОТЫ СО СТЕКОМ ===\n");
    printf("1. Ввод чисел и сортировка прямым включением\n");
    printf("2. Сортировка слиянием\n");
    printf("3. Сравнение методов сортировки\n");
    printf("4. Выход\n");
    printf("Выберите опцию: ");
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian"); // Русский язык

    // Обработка аргументов командной строки
    if (argc > 1)
    {
        handle_command_line_args(argc, argv);
        return 0;
    }

    int choice;
    Elem *top = NULL;

    // Ввод чисел в начале
    input_numbers(&top);
    printf("Создан стек из %d элементов: ", stack_size(top));
    print_stack(top);

    do
    {
        show_menu();
        scanf("%d", &choice);
        getchar(); // Очистка буфера

        switch (choice)
        {
        case 1:
        {
            printf("До сортировки: ");
            print_stack(top);
            insertion_sort_stack(&top);
            printf("После сортировки: ");
            print_stack(top);
            break;
        }

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
            printf("Выход из программы...\n");
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    } while (choice != 4);
    clear_stack(&top);
    return 0;
}