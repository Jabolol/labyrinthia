/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/generator.h"
#include "../include/oop/stack.h"
#include "../include/bs_dante.h"

void generator_visit_neighbour(
    GeneratorClass *self, cell_t ***neighbours, int32_t length)
{
    cell_t **not_visited_tuple = neighbours[rand() % length];
    cell_t *inner = *not_visited_tuple;
    cell_t *outer = *(not_visited_tuple + 1);
    inner->value = outer->value = '*';
    inner->visited = outer->visited = true;
    self->stack->push(self->stack, inner);
    self->stack->push(self->stack, outer);
}

void generator_backtrack(GeneratorClass *self)
{
    self->stack->pop(self->stack);
    self->stack->pop(self->stack);
}

void generator_free_neighbours(cell_t ***neighbours)
{
    for (int32_t i = 0; i < 4; i++) {
        free(neighbours[i]);
    }
    free(neighbours);
}

void generator_generate_maze(GeneratorClass *self)
{
    cell_t ***neighbours = calloc(4, sizeof(cell_t **));
    int32_t length = 0;

    cell_t *start = self->grid[0][0];
    start->value = '*';
    start->visited = true;
    self->stack->push(self->stack, start);

    for (int32_t i = 0; i < 4; i++)
        neighbours[i] = calloc(2, sizeof(cell_t *));
    while (self->stack->peek(self->stack) != NULL) {
        cell_t *current_cell = self->stack->peek(self->stack);
        self->get_neighbours(self, current_cell, neighbours, &length);
        if (length > 0) {
            self->visit_neighbour(self, neighbours, length);
        } else {
            self->backtrack(self);
        }
    }
    self->free_neighbours(neighbours);
}
