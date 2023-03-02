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
    size_t columns;
    node_t *pool;
    node_t **data;
    TreeClass *tree;
    /* Methods */
    void (*load_file)(SolverClass *, char *);
    void (*load_nodes)(SolverClass *);
} SolverClass;
extern const class_t *Solver;
#endif
