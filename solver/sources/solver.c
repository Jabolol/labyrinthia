/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/solver.h"

void solver_constructor(void *ptr, va_list __attribute__((unused)) * ap)
{
    SolverClass *self = (SolverClass *) ptr;
    if (!((self->adjacent = calloc(4, sizeof(node_t *))))) {
        fprintf(stderr, "Failed calloc allocation\n");
        exit(EXIT_ERROR);
    }
}

void solver_destructor(void *ptr)
{
    SolverClass *self = (SolverClass *) ptr;
    destroy_class(self->open);
    destroy_class(self->close);
    munmap(self->addr, self->size);
    free(self->pool);
    free(self->data);
    free(self->adjacent);
}

const SolverClass init_solver = {
    {
        ._size = sizeof(SolverClass),
        ._name = "Solver",
        ._constructor = &solver_constructor,
        ._destructor = &solver_destructor,
    },
    .addr = NULL,
    .data = NULL,
    .pool = NULL,
    .adjacent = NULL,
    .smallest = NULL,
    .target = NULL,
    .size = 0,
    .columns = 0,
    .offset = 0,
    .error = false,
    .load_file = &solver_load_path,
    .load_nodes = &solver_load_nodes,
    .get_adjacent = &solver_get_adjacent,
    .start_solver = &solver_start_solver,
    .prune_adjacent = &solver_prune_adjacent,
    .handle_valid_adjacent = &solver_handle_valid_adjacent,
    .print_maze = &solver_print_maze,
    .fill_nodes = &solver_fill_nodes,
    .solve_maze = &solver_solve_maze,
    .is_valid = &solver_is_valid,
};

const class_t *Solver = (const class_t *) &init_solver;
