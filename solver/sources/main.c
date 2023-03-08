/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/solver.h"

// TODO(jabolo): Cleanup this code :)
// TODO(jabolo): Error handling
int main(int __attribute__((unused)) argc, char **argv)
{
    SolverClass *self = new_class(Solver);
    self->start_solver(self, *(argv + 1));

    while (self->open->leaf_count > 0) {
        self->smallest = self->open->get_smallest(self->open->root);
        leaf_t *out =
            self->open->remove_leaf(self->open, self->smallest->node);
        self->close->insert_leaf(self->close, out->node);
        if (memcmp(&self->smallest->node->coords, &self->target->coords,
                sizeof(self->target->coords))
            == 0)
            self->print_maze(self, out, self->smallest);
        self->get_adjacent(self, &self->smallest->node->coords);
        self->prune_adjacent(self);
        self->open->free(self->open, out);
    }
    write(STDOUT_FILENO, "no solution found", 17);
    destroy_class(self);
    return EXIT_ERROR;
}
