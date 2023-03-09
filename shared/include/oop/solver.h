/*
** EPITECH PROJECT, 2023
** solver.h
** File description:
** dante solver header file
*/

#include <assert.h>
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
    bool error;
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
    void (*print_maze)(SolverClass *, leaf_t *, leaf_t *);
    void (*solve_maze)(SolverClass *);
    bool (*is_valid)(SolverClass *);
} SolverClass;
void solver_start_solver(SolverClass *, char *);
void solver_get_adjacent(SolverClass *, coords_t *);
void solver_prune_adjacent(SolverClass *);
void solver_handle_valid_adjacent(SolverClass *, node_t *);
void solver_print_maze(SolverClass *, leaf_t *, leaf_t *);
void solver_solve_maze(SolverClass *);
void solver_load_path(SolverClass *, char *);
void solver_fill_nodes(SolverClass *);
void solver_load_nodes(SolverClass *);
bool solver_is_valid(SolverClass *);
extern const class_t *Solver;
#endif
