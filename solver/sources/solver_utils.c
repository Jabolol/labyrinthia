/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/solver.h"

void solver_get_adjacent(SolverClass *self, coords_t *coords)
{
    int32_t rows = (self->size - self->offset) / self->columns;
    int32_t cols = self->columns;

    int32_t dx[4] = {0, -1, 0, 1};
    int32_t dy[4] = {-1, 0, 1, 0};

    for (int32_t i = 0; i < 4; i++) {
        int32_t nx = coords->x + *(dx + i);
        int32_t ny = coords->y + *(dy + i);
        *(self->adjacent + i) = NULL;
        if (ny >= 0 && ny < rows && nx >= 0 && nx < cols
            && (ny == coords->y || nx == coords->x))
            *(self->adjacent + i) = *(self->data + (ny * self->columns) + nx);
    }
}

void solver_start_solver(SolverClass *self, char *path)
{
    self->load_file(self, path);
    self->load_nodes(self);
    self->target = *(self->data + self->size - self->offset - 1);
    self->open->insert_leaf(self->open, *self->data);
}

void solver_prune_adjacent(SolverClass *self)
{
    for (int8_t i = 0; i < 4; i++) {
        if (!*(self->adjacent + i) || !(*(self->adjacent + i))->walkable
            || self->close->get_leaf(self->close, (*(self->adjacent + i)))
                != NULL) {
            continue;
        }
        self->handle_valid_adjacent(self, *(self->adjacent + i));
    }
}

void solver_handle_valid_adjacent(SolverClass *self, node_t *adjacent)
{
    double h = MANHATTAN(adjacent->coords, self->target->coords);

    if (self->open->get_leaf(self->open, adjacent) == NULL
        || h < adjacent->costs.h) {
        double g = MANHATTAN(adjacent->coords, (*self->data)->coords);
        double f = g + h;
        adjacent->parent = self->smallest->node;
        adjacent->costs.f = f;
        adjacent->costs.g = g;
        adjacent->costs.h = h;
        if (self->open->get_leaf(self->open, adjacent) == NULL) {
            self->open->insert_leaf(self->open, adjacent);
        }
    }
}

noreturn int solver_print_maze(
    SolverClass *self, leaf_t *out, leaf_t *smallest)
{
    node_t *curr = smallest->node;
    while (curr) {
        *((char *) self->addr + (curr->coords.y * self->columns)
            + curr->coords.x + curr->coords.y) = 'o';
        curr = curr->parent;
    }
    self->open->free(self->open, out);
    write(STDOUT_FILENO, (char *) self->addr, self->size);
    destroy_class(self);
    exit(0);
}
