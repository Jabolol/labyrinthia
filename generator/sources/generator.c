/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/generator.h"
#include "../include/bs_dante.h"

void generator_constructor(void *ptr, va_list *args)
{
    GeneratorClass *self = (GeneratorClass *) ptr;
    self->width = va_arg(*args, size_t);
    self->height = va_arg(*args, size_t);
    self->total = self->width * self->height;
    self->stack = new_class(Stack, self->total);
    self->grid = malloc(self->height * sizeof(cell_t **));
    self->chunk = malloc(self->width * self->height * sizeof(cell_t));

    for (size_t y = 0; y < self->height; y++) {
        self->grid[y] = malloc(self->width * sizeof(cell_t *));
        for (size_t x = 0; x < self->width; x++) {
            self->grid[y][x] = self->chunk + (y * self->width + x);
            self->grid[y][x]->value = 'X';
            self->grid[y][x]->visited = false;
            self->grid[y][x]->x = x;
            self->grid[y][x]->y = y;
        }
    }
}

void generator_destructor(void *ptr)
{
    GeneratorClass *self = (GeneratorClass *) ptr;
    destroy_class(self->stack);
    for (size_t y = 0; y < self->height; y++) {
        free(self->grid[y]);
    }
    free(self->grid);
    free(self->chunk);
}

void generator_add_neighbour(
    GeneratorClass *self, neighbour_t *meta, cell_t ***neighbours, size_t *off)
{
    size_t in_y = meta->y + meta->y_dir, ou_y = meta->y + (meta->y_dir * 2);
    size_t in_x = meta->x + meta->x_dir, ou_x = meta->x + (meta->x_dir * 2);
    cell_t *inner = self->grid[in_y][in_x], *outer = self->grid[ou_y][ou_x];

    if (!inner->visited && !outer->visited) {
        *(*(neighbours + *off)) = inner, *(*(neighbours + *off) + 1) = outer;
        *off = *off + 1;
    }
}

void generator_get_neighbours(
    GeneratorClass *self, cell_t *cell, cell_t ***neighbours, int32_t *length)
{
    size_t x = cell->x, y = cell->y, off = 0;

    neighbour_t dirs[4] = {
        {x, y, -1, 0, x > 1},
        {x, y, +1, 0, x < self->width - 2},
        {x, y, 0, -1, y > 1},
        {x, y, 0, +1, y < self->height - 2},
    };

    for (int32_t i = 0; i < 4; i++) {
        if (dirs[i]._condition) {
            self->add_neighbour(self, &dirs[i], neighbours, &off);
        }
    }
    *length = off;
}

void generator_print_grid(GeneratorClass *self)
{
    char buffer[self->height * self->width + self->height];
    size_t pos = 0;

    for (size_t y = 0; y < self->height; y++) {
        for (size_t x = 0; x < self->width; x++) {
            buffer[pos++] = self->is_perfect ? self->grid[y][x]->value : ({
                double r = (double) rand() / RAND_MAX;
                r < 0.2 ? '*' : self->grid[y][x]->value;
            });
        }
        if (y != self->height - 1) {
            buffer[pos++] = '\n';
        }
    }

    buffer[pos - 1] = buffer[pos - 2] = buffer[pos - (self->width + 2)] = '*';
    write(STDOUT_FILENO, buffer, pos);
}

const GeneratorClass init_generator = {
    {
        ._size = sizeof(GeneratorClass),
        ._name = "Generator",
        ._constructor = &generator_constructor,
        ._destructor = &generator_destructor,
    },
    .stack = NULL,
    .total = 0,
    .width = 0,
    .height = 0,
    .is_perfect = false,
    .get_neighbours = &generator_get_neighbours,
    .add_neighbour = &generator_add_neighbour,
    .print_grid = &generator_print_grid,
    .visit_neighbour = &generator_visit_neighbour,
    .backtrack = &generator_backtrack,
    .free_neighbours = &generator_free_neighbours,
    .generate_maze = &generator_generate_maze,
};

const class_t *Generator = (const class_t *) &init_generator;
