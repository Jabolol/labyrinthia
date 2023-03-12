/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/stack.h"
#include "../include/bs_dante.h"

void stack_constructor(void *ptr, va_list *args)
{
    StackClass *self = (StackClass *) ptr;
    self->size = va_arg(*args, size_t);
    self->stack = malloc(sizeof(*self->stack));
    self->stack->size = self->size;
    self->stack->pool = malloc(self->size * sizeof(cell_t *));
    self->stack->top = self->stack->pool;
    for (size_t i = 0; i < self->size; i++) {
        *(self->stack->pool + i) = NULL;
    }
}

void stack_destructor(void *ptr)
{
    StackClass *self = (StackClass *) ptr;
    free(self->stack->pool);
    free(self->stack);
}

void stack_push(StackClass *self, cell_t *ptr)
{
    if (self->stack->top == self->stack->pool + self->stack->size) {
        return;
    }
    *(self->stack->top) = ptr;
    self->stack->top += 1;
}

cell_t *stack_pop(StackClass *self)
{
    if (self->stack->top <= self->stack->pool) {
        return NULL;
    }
    self->stack->top -= 1;
    return *(self->stack->top);
}

cell_t *stack_peek(StackClass *self)
{
    if (self->stack->top <= self->stack->pool) {
        return NULL;
    }
    return *(self->stack->top - 1);
}

const StackClass init_stack = {
    {
        ._size = sizeof(StackClass),
        ._name = "Stack",
        ._constructor = &stack_constructor,
        ._destructor = &stack_destructor,
    },
    .size = 0,
    .stack = NULL,
    .push = &stack_push,
    .pop = &stack_pop,
    .peek = &stack_peek,
};

const class_t *Stack = (const class_t *) &init_stack;
