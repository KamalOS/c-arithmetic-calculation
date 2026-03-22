#include "generic_stack.h"

// Error Handling
#define EXIT_IF(cnd, msg) ({ if ((cnd)) { fprintf(stderr, msg); exit(EXIT_FAILURE); } })
#define TEST_INIT_STACK(st) ({ if ((st) == NULL) return; })

// initialize
stack_t* init_stack(size_t size)
{
    stack_t *stack = malloc(sizeof *stack * 1);
    EXIT_IF (stack == NULL, "not enough memory!\n");

    if (size < 1) {
        fprintf(stderr, "Impossible size!\n");
        exit(EXIT_FAILURE);
    }

    stack->top = NULL;
    stack->size = size;

    return stack;
}

// add item to top
void push(void* const data, stack_t* const stack)
{
    TEST_INIT_STACK(stack);

    {
        int i;
        node_t *node = malloc(sizeof *node * 1);
        EXIT_IF (node == NULL, "not enough memory!\n");

        node->data = malloc(sizeof (stack->size) * 1);
        EXIT_IF (node == NULL, "not enough memory!\n");

        // node->data = data;
        for (i = 0; i < stack->size; ++i) {
            *(char *)(node->data + i) = *(char *)(data + i);
        }

        node->next = stack->top;
        stack->top = node;
    }
}

// delete the item at the top
void pop(stack_t *const stack)
{
    TEST_INIT_STACK(stack);

    {
        node_t *node = stack->top;

        if (node == NULL)
            return;

        stack->top = stack->top->next;
        free(node);
    }
}

// is a stack empty?
bool is_empty(stack_t const*const stack)
{
    return (stack == NULL || stack->top == NULL);
}

// printing and clear the stack
void print_stack(stack_t* stack, void (*print)(void const*const))
{
    printf("Stack: top ->");
    while (!is_empty(stack))
    {
        printf(" ");
        (*print)(stack->top->data);
        printf(" ->");
        pop(stack);
    }
    printf(" NULL\n");
}
// ready to use for printing
void print_int(void const*const data) {
    printf("%d", *(int *)data);
}
void print_float(void const*const data) {
    printf("%f", *(float *)data);
}
void print_char(void const*const data) {
    printf("%c", *(char *)data);
}
void print_string(void const*const data) {
    printf("%s", (char *)data);
}
