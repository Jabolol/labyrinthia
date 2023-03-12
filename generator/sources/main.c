/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/generator.h"
#include "../include/oop/stack.h"
#include "../include/bs_dante.h"

// TBD
int32_t perfect_maze(GeneratorClass *self, size_t width, size_t height)
{
    srand(time(NULL));
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s width height\n", *argv);
        return EXIT_FAILURE;
    }
    size_t width = atoi(argv[1]), height = atoi(argv[2]);
    GeneratorClass *self = new_class(Generator, width, height);
    cell_t ***neighbours = calloc(4, sizeof(cell_t **));
    for (int32_t i = 0; i < 4; i++) {
        neighbours[i] = calloc(2, sizeof(cell_t *));
    }
    int32_t length = 0;
    cell_t *start = self->grid[0][0];
    start->value = '*';
    start->visited = true;
    self->stack->push(self->stack, start);

    while (self->stack->peek(self->stack) != NULL) {
        cell_t *current_cell = self->stack->peek(self->stack);
        self->get_neighbours(self, current_cell, neighbours, &length);
        if (length > 0) {
            cell_t **not_visited_tuple = neighbours[rand() % length];
            cell_t *inner = *not_visited_tuple,
                   *outer = *(not_visited_tuple + 1);
            inner->value = outer->value = '*';
            inner->visited = outer->visited = true;
            self->stack->push(self->stack, inner);
            self->stack->push(self->stack, outer);
        } else {
            self->stack->pop(self->stack);
            self->stack->pop(self->stack);
        }
    }

    for (size_t y = 0; y < self->height; y++) {
        for (size_t x = 0; x < self->width; x++) {
            write(1, &self->grid[y][x]->value, 1);
        }
        if (y != self->height - 1) {
            write(1, "\n", 1);
        }
    }

    // free --->
    for (int32_t i = 0; i < 4; i++) {
        free(neighbours[i]);
    }
    free(neighbours);
    destroy_class(self);
    return EXIT_SUCCESS;
}
