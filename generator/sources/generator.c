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
    for (size_t y = 0; y < self->height; y++) {
        self->grid[y] = malloc(self->width * sizeof(cell_t *));
        for (size_t x = 0; x < self->width; x++) {
            self->grid[y][x] = malloc(sizeof(cell_t));
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
        for (size_t x = 0; x < self->width; x++) {
            free(self->grid[y][x]);
        }
        free(self->grid[y]);
    }
    free(self->grid);
}

void generator_get_neighbours(
    GeneratorClass *self, cell_t *cell, cell_t ***neighbours, int32_t *length)
{
    size_t x = cell->x, y = cell->y;
    size_t off = 0;

    if (x > 1) {
        cell_t *inner = self->grid[y][x - 1];
        cell_t *outer = self->grid[y][x - 2];
        if (!inner->visited && !outer->visited) {
            *(*(neighbours + off)) = inner;
            *(*(neighbours + off) + 1) = outer;
            off = off + 1;
        }
    }
    if (x < self->width - 2) {
        cell_t *inner = self->grid[y][x + 1];
        cell_t *outer = self->grid[y][x + 2];
        if (!inner->visited && !outer->visited) {
            *(*(neighbours + off)) = inner;
            *(*(neighbours + off) + 1) = outer;
            off = off + 1;
        }
    }
    if (y > 1) {
        cell_t *inner = self->grid[y - 1][x];
        cell_t *outer = self->grid[y - 2][x];
        if (!inner->visited && !outer->visited) {
            *(*(neighbours + off)) = inner;
            *(*(neighbours + off) + 1) = outer;
            off = off + 1;
        }
    }
    if (y < self->height - 2) {
        cell_t *inner = self->grid[y + 1][x];
        cell_t *outer = self->grid[y + 2][x];
        if (!inner->visited && !outer->visited) {
            *(*(neighbours + off)) = inner;
            *(*(neighbours + off) + 1) = outer;
            off = off + 1;
        }
    }
    *length = off;
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
    .get_neighbours = &generator_get_neighbours,
};

const class_t *Generator = (const class_t *) &init_generator;
