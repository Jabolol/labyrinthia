/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/solver.h"

int main(int __attribute__((unused)) argc, char **argv)
{
    SolverClass *self = new_class(Solver);
    self->start_solver(self, *(argv + 1));
    if (self->error || (((self->error = !self->is_valid(self))))) {
        destroy_class(self);
        return EXIT_ERROR;
    }
    self->solve_maze(self);
    destroy_class(self);
    return EXIT_ERROR;
}
