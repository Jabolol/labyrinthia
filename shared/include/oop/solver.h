/*
** EPITECH PROJECT, 2023
** solver.h
** File description:
** dante solver header file
*/

#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "./tree.h"
#include "oop.h"

#ifndef __DANTE_SOLVER
    #define __DANTE_SOLVER
typedef struct solver_aux SolverClass;
typedef struct solver_aux {
    /* Inheritance */
    class_t parent;
    /* Properties */
    void *addr;
    size_t size;
    size_t offset;
    size_t columns;
    node_t *pool;
    node_t *target;
    leaf_t *smallest;
    node_t **data;
    node_t **adjacent;
    TreeClass *open;
    TreeClass *close;
    /* Methods */
    void (*load_file)(SolverClass *, char *);
    void (*load_nodes)(SolverClass *);
    void (*get_adjacent)(SolverClass *, coords_t *);
    void (*start_solver)(SolverClass *, char *);
    void (*fill_nodes)(SolverClass *);
    void (*prune_adjacent)(SolverClass *);
    void (*handle_valid_adjacent)(SolverClass *, node_t *);
    int (*print_maze)(SolverClass *, leaf_t *, leaf_t *);
} SolverClass;
void solver_start_solver(SolverClass *self, char *path);
void solver_get_adjacent(SolverClass *self, coords_t *coords);
void solver_prune_adjacent(SolverClass *self);
void solver_handle_valid_adjacent(SolverClass *self, node_t *adjacent);
int solver_print_maze(SolverClass *self, leaf_t *out, leaf_t *smallest);
extern const class_t *Solver;
#endif
