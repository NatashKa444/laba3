#include "stack.h"

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("Ошибка выделения памяти для стека!\n");
        exit(1);
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack *stack, int data)
{
    Elem *newElem = (Elem *)malloc(sizeof(Elem));
    if (newElem == NULL)
    {
        printf("Ошибка выделения памяти для нового элемента!\n");
        exit(1);
    }

    newElem->data = data;
    newElem->next = stack->top;
    stack->top = newElem;
    stack->size++;
}

int pop(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Стек пуст!\n");
        return -1;
    }

    Elem *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;

    return data;
}

void printStack(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("Стек пуст.\n");
        return;
    }

    printf("Стек (%d элементов): ", stack->size);
    Elem *current = stack->top;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void insertAtPosition(Stack *stack, int position, int data)
{
    if (position < 1 || position > stack->size + 1)
    {
        printf("Неверная позиция! Допустимые позиции: 1-%d\n", stack->size + 1);
        return;
    }

    if (position == 1)
    {
        push(stack, data);
        return;
    }

    Elem *current = stack->top;
    for (int i = 1; i < position - 1; i++)
    {
        current = current->next;
    }

    Elem *newElem = (Elem *)malloc(sizeof(Elem));
    newElem->data = data;
    newElem->next = current->next;
    current->next = newElem;
    stack->size++;
}

void deleteAtPosition(Stack *stack, int position)
{
    if (position < 1 || position > stack->size)
    {
        printf("Неверная позиция ! Допустимые позиции:1-%d\n", stack->size);
        return;
    }

    if (position == 1)
    {
        pop(stack);
        return;
    }

    Elem *current = stack->top;
    for (int i = 1; i < position - 1; i++)
    {
        current = current->next;
    }

    Elem *toDelete = current->next;
    current->next = toDelete->next;
    free(toDelete);
    stack->size--;
}

void editAtPosition(Stack *stack, int position, int newData)
{
    if (position < 1 || position > stack->size)
    {
        printf("Неверная позиция! Допустимые позиции: 1-%d\n", stack->size);
        return;
    }

    Elem *current = stack->top;
    for (int i = 1; i < position; i++)
    {
        current = current->next;
    }

    current->data = newData;
    printf("Элемент на позиции %d изменен на %d\n", position, newData);
}

void freeStack(Stack *stack)
{
    while (stack->top != NULL)
    {
        pop(stack);
    }
    free(stack);
}

int getStackSize(Stack *stack)
{
    return stack->size;
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int askToContinue()
{
    char answer;
    printf("\nХотите выполнить еще одну операцию? (1 - да, 0 - нет): ");
    if (scanf(" %c", &answer) != 1)
    {
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();
    return answer == '1';
}