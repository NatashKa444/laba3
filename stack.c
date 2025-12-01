#include "stack.h"

// ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜
void push(Elem **top, int value)
{
    Elem *p = (Elem *)malloc(sizeof(Elem)); // ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜
    p->data = value;                        // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
    p->next = *top;                         // ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    *top = p;                               // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜
}

// ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜
int pop(Elem **top)
{
    if (*top == NULL)
        return -1; // ˜˜˜˜ ˜˜˜˜ ˜˜˜˜

    int val = (*top)->data; // ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
    Elem *p = *top;         // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜
    *top = (*top)->next;    // ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜
    free(p);                // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
    return val;             // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜
}

// ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜
int is_empty(Elem *top)
{
    return top == NULL;
}

// ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜
void clear_stack(Elem **top)
{
    while (*top != NULL)
    {
        pop(top);
    }
}

// ˜˜˜˜˜˜ ˜˜˜˜˜
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

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜
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