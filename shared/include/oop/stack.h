/*
** EPITECH PROJECT, 2023
** solver.h
** File description:
** dante solver header file
*/

#include "oop.h"
#include "../bs_dante.h"

#ifndef __DANTE_STACK
    #define __DANTE_STACK
typedef struct {
    char value;
    bool visited;
    int32_t x;
    int32_t y;
} cell_t;
typedef struct {
    cell_t **pool;
    cell_t **top;
    size_t size;
} my_stack_t;
typedef struct stack_aux StackClass;
typedef struct stack_aux {
    /* Inheritance */
    class_t parent;
    /* Properties */
    my_stack_t *stack;
    size_t size;
    /* Methods */
    void (*push)(StackClass *, cell_t *);
    cell_t *(*pop)(StackClass *);
    cell_t *(*peek)(StackClass *);
} StackClass;
extern const class_t *Stack;
#endif
