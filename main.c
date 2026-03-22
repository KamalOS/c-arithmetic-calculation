#include "generic_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>

#define INF INT_MAX
#define _INF INT_MIN

int eval(int a, int b, char op)
{
    switch (op) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        case '^': return pow(a, b);
        default: return _INF;
    }
    return _INF;
}

// calcule d'une expression postfix en utilisant une pile
static inline void calc_postfix(stack_t* pile, char exp)
{
    if (isdigit(exp)) {
            int val = exp - '0';
            push(&val, pile);
        }
    else if (exp == '+' || exp == '-' || exp == '*' || exp == '/' || exp == '^') {
        int a, b;

        b = *(int *)pile->top->data;
        pop(pile);

        a = *(int *)pile->top->data;
        pop(pile);

        int res = eval(a, b, exp);
        push(&res, pile);
    }
}

int main()
{
    char infix[100] = "", postfix[100] = "";
    char pre[] = {'-', '+', '*', '/'};
    int i, pre_n = sizeof pre / sizeof *pre;
    stack_t *pile = init_stack(sizeof(char));

    printf("Expr. infix: ");
    gets(infix);

    for (i = 0; i < strlen(infix); ++i) {
        if (isalpha(infix[i])) {
            postfix[strlen(postfix)] = infix[i];
            postfix[strlen(postfix) + 1] = '\0';
        }

        else if (infix[i] == '(') {
            push(&infix[i], pile);
        }

        else if (infix[i] == ')') {
            //pop(pile);
            char op;
            while ((op = *(char *)pile->top->data) != '(') {
                postfix[strlen(postfix)] = op;
                postfix[strlen(postfix) + 1] = '\0';
                pop(pile);
            }
        }

        else {
            int j;
            int a, b;

            if (is_empty(pile)) {
                push(&infix[i], pile);
                continue;
            }

            char op = *(char *)pile->top->data;
            for (j = 0; j < pre_n; ++j) {
                if (infix[i] == pre[j]) a = j;
                if (op == pre[j]) b = j;
            }
            if (b >= a) {
                pop(pile);
                postfix[strlen(postfix)] = op;
                postfix[strlen(postfix) + 1] = '\0';
                push(&infix[i], pile);
            }
        }
    }

    while (!is_empty(pile)) {
        char op = *(char *)pile->top->data;
        postfix[strlen(postfix)] = op;
        postfix[strlen(postfix) + 1] = '\0';
        pop(pile);
    }

    puts(postfix);

//    while ((exp = getchar()) != '\n')
//        calc_postfix(pile, exp);
//
    //print_stack(pile, print_char);

    return 0;
}
