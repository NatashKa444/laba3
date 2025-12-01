#include "stack.h"

// Добавление элемента в стек
void push(Elem **top, int value)
{
    Elem *p = (Elem *)malloc(sizeof(Elem)); // Создаем новый элемент
    p->data = value;                        // Записываем число
    p->next = *top;                         // Связываем с предыдущим элементом
    *top = p;                               // Обновляем вершину стека
}

// Удаление элемента из стека
int pop(Elem **top)
{
    if (*top == NULL)
        return -1; // Если стек пуст

    int val = (*top)->data; // Сохраняем данные
    Elem *p = *top;         // Запоминаем элемент для удаления
    *top = (*top)->next;    // Переходим к следующему элементу
    free(p);                // Освобождаем память
    return val;             // Возвращаем значение
}

// Проверка пустоты стека
int is_empty(Elem *top)
{
    return top == NULL;
}

// Очистка всего стека
void clear_stack(Elem **top)
{
    while (*top != NULL)
    {
        pop(top);
    }
}

// Печать стека
void print_stack(Elem *top)
{
    Elem *current = top;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Подсчет размера стека
int stack_size(Elem *top)
{
    int count = 0;
    Elem *current = top;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}