#ifndef GENERIC_STACK_H_INCLUDED
#define GENERIC_STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// node
typedef struct node_t {
    void* data;
    struct node_t* next;
} node_t;
// control structure
typedef struct stack_t {
    node_t* top;
    size_t size; // sizeof one item
} stack_t;

// initialize
stack_t* init_stack(size_t size);

// add item to top
void push(void* const data, stack_t *const stack);

// delete the item at the top
void pop(stack_t *const stack);

// is a stack empty?
bool is_empty(stack_t const*const stack);

// printing and clear the stack
void print_stack(stack_t* stack, void (*print)(void const*const));
// ready to use for printing
void print_int(void const*const data);
void print_float(void const*const data);
void print_char(void const*const data);
void print_string(void const*const data);


#endif // GENERIC_STACK_H_INCLUDED
