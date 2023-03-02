/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/bs_dante.h"
#include "../include/oop/solver.h"

int main(void)
{
    SolverClass *self __attribute__((cleanup(free_class))) = new_class(Solver);
    self->load_file(self, "./maze.txt");
    self->load_nodes(self);
    self->tree->insert_leaf(self->tree, *self->data);
    leaf_t *leaf = self->tree->get_smallest(self->tree->tree);
    printf("-> %p\n", leaf);
    return 0;
}
