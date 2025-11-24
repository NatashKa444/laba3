#include "stack.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    if (argc == 3)
    {
        // if (argv[1][0] == '-' && argv[1][1] == '-' && argv[1][2] == 'f') {
        //     Stack* stack = loadStackFromFile(argv[2]);
        //     if (stack != NULL) {
        //         printf("Исходный ряд: ");
        //         printStack(stack);
        //         Stack* sorted = mergeSort(stack);
        //         printf("Отсортированный ряд: ");
        //         printStack(sorted);

        //         saveStackToFile(sorted, "sorted.txt");

        //         freeStack(stack);
        //         freeStack(sorted);
        //     }
        //     return 0;
        // }
    }
    Stack *stack = createStack();
    int choice;
    do
    {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Ввести числа\n");
        printf("2. Вывести стек\n");
        printf("3. Добавить элемент\n");
        printf("4. Удалить элемент\n");
        printf("5. Редактировать элемент\n");
        printf("6. Сортировка включением\n");
        printf("7. Сортировка слиянием\n");
        printf("8. Сохранить в файл\n");
        printf("9. Загрузить из файла\n");
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
        {
            printf("Введите числа через пробел: ");
            char input[1000];
            fgets(input, 1000, stdin);

            freeStack(stack);
            stack = createStack();

            char *token = input;
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
                }
                else
                {
                    token++;
                }
            }
            printf("Создан стек из %d элементов\n", stack->size);
            break;
        }

        case 2:
            printStack(stack);
            break;

        case 3:
        {
            int data;
            printf("Введите число: ");
            if (scanf("%d", &data) == 1)
            {
                push(stack, data);
                printf("Элемент %d добавлен\n", data);
            }
            clearInputBuffer();
            break;
        }

        case 4:
            if (stack->size > 0)
            {
                int data = pop(stack);
                printf("Удален элемент: %d\n", data);
            }
            else
            {
                printf("Стек пуст!\n");
            }
            break;

        case 5:
        {
            int position, newData;
            printf("Введите позицию (1-%d): ", stack->size);
            if (scanf("%d", &position) == 1)
            {
                printf("Введите новое значение: ");
                if (scanf("%d", &newData) == 1)
                {
                    editAtPosition(stack, position, newData);
                }
            }
            clearInputBuffer();
            break;
        }

        case 6:
            // if (stack->size > 0) {
            //     insertionSort(stack);
            //     printf("Стек отсортирован!\n");
            //     printStack(stack);
            // } else {
            //     printf("Стек пуст!\n");
            // }
            // break;

        case 7:
            // if (stack->size > 0) {
            //     Stack* sorted = mergeSort(stack);
            //     freeStack(stack);
            //     stack = sorted;
            //     printf("Стек отсортирован!\n");
            //     printStack(stack);
            // } else {
            //     printf("Стек пуст!\n");
            // }
            // break;

        case 8:
            // if (stack->size > 0) {
            //     saveStackToFile(stack, "stack.txt");
            // } else {
            //     printf("Стек пуст!\n");
            // }
            // break;

        case 9:
        {
            // Stack* loaded = loadStackFromFile("stack.txt");
            // if (loaded != NULL) {
            //     freeStack(stack);
            //     stack = loaded;
            // }
            // break;
        }

        case 0:
            printf("Выход\n");
            break;

        default:
            printf("Неверный выбор!\n");
        }

    } while (choice != 0 && askToContinue());

    freeStack(stack);
    return 0;
}