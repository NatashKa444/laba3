#include "stack.h"

// Очистка буфера ввода
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Ввод последовательности чисел
Stack *inputStack()
{
    char input[1000];
    printf("Введите последовательность чисел через пробел: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("Ошибка ввода!\n");
        return NULL;
    }

    Stack *stack = createStack();
    char *token = input;
    int numbersCount = 0;

    // Разбираем введенную строку на числа
    while (*token)
    {
        if (*token >= '0' && *token <= '9')
        {
            int num = 0;
            while (*token >= '0' && *token <= '9')
            {
                num = num * 10 + (*token - '0');
                token++;
            }
            push(stack, num);
            numbersCount++;
        }
        else
        {
            token++;
        }
    }

    if (numbersCount == 0)
    {
        printf("Ошибка: не введено ни одного числа!\n");
        freeStack(stack);
        return NULL;
    }

    printf("Создан стек из %d элементов\n", numbersCount);
    return stack;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    // Режим --file
    if (argc == 3 && strcmp(argv[1], "--file") == 0)
    {
        Stack *stack = loadStackFromFile(argv[2]);
        if (stack != NULL)
        {
            printf("Исходный ряд: ");
            printStack(stack);

            // Сохраняем исходный ряд
            saveStackToFile(stack, "input.txt");

            // Сортируем прямым включением
            Stack *sorted = createStack();
            Elem *current = stack->top;
            while (current != NULL)
            {
                push(sorted, current->inf); // Копируем данные
                current = current->link;    // Переходим по ссылкам
            }
            insertionSort(sorted);

            printf("Отсортированный ряд: ");
            printStack(sorted);

            // Сохраняем отсортированный ряд
            saveStackToFile(sorted, "output.txt");

            freeStack(stack);
            freeStack(sorted);
        }
        return 0;
    }

    // Основной режим - ввод последовательности
    Stack *stack = NULL;

    printf("=== ЛАБОРАТОРНАЯ РАБОТА: СОРТИРОВКА СТЕКА ===\n\n");

    // Ввод последовательности
    while (stack == NULL)
    {
        stack = inputStack();
        if (stack == NULL)
        {
            printf("Попробуйте еще раз.\n\n");
        }
    }

    int choice, data;

    do
    {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Вывести стек\n");
        printf("2. Добавить элемент\n");
        printf("3. Удалить элемент\n");
        printf("4. Сортировка прямым включением\n");
        printf("5. Сортировка слиянием\n");
        printf("6. Сохранить стек в файл\n");
        printf("7. Загрузить стек из файла\n");
        printf("8. Сравнить методы сортировки\n");
        printf("0. Выход\n");
        printf("Выберите: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Ошибка ввода!\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            printf("Текущий стек: ");
            printStack(stack);
            break;

        case 2:
            printf("Введите число для добавления: ");
            if (scanf("%d", &data) == 1)
            {
                push(stack, data);
                printf("Элемент %d добавлен в стек!\n", data);
            }
            else
            {
                printf("Ошибка ввода!\n");
            }
            clearInputBuffer();
            break;

        case 3:
            data = pop(stack);
            if (data != -1)
            {
                printf("Элемент %d удален из стека!\n", data);
            }
            else
            {
                printf("Стек пуст!\n");
            }
            break;

        case 4:
            if (stack->size > 0)
            {
                insertionSort(stack);
                printf("Стек отсортирован методом прямого включения!\n");
                printf("Результат: ");
                printStack(stack);
            }
            else
            {
                printf("Стек пуст!\n");
            }
            break;

        case 5:
            if (stack->size > 0)
            {
                Stack *sorted = mergeSort(stack);
                freeStack(stack);
                stack = sorted;
                printf("Стек отсортирован методом слияния!\n");
                printf("Результат: ");
                printStack(stack);
            }
            else
            {
                printf("Стек пуст!\n");
            }
            break;

        case 6:
            if (stack->size > 0)
            {
                saveStackToFile(stack, "stack.txt");
            }
            else
            {
                printf("Стек пуст!\n");
            }
            break;

        case 7:
        {
            Stack *loaded = loadStackFromFile("stack.txt");
            if (loaded != NULL)
            {
                freeStack(stack);
                stack = loaded;
            }
            break;
        }

        case 8:
            compareSorts();
            break;

        case 0:
            printf("Выход из программы\n");
            break;

        default:
            printf("Неверный выбор!\n");
        }

    } while (choice != 0);

    freeStack(stack);
    return 0;
}