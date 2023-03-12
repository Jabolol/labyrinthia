/*
** EPITECH PROJECT, 2023
** solver.h
** File description:
** dante solver header file
*/

#include "oop.h"
#include "../bs_dante.h"
#include "./stack.h"

#ifndef __DANTE_GENERATOR
    #define __DANTE_GENERATOR
typedef struct generator_aux GeneratorClass;
typedef struct generator_aux {
    /* Inheritance */
    class_t parent;
    /* Properties */
    size_t width;
    StackClass *stack;
    size_t height;
    size_t total;
    cell_t ***grid;
    /* Methods */
    void (*get_neighbours)(GeneratorClass *, cell_t *, cell_t ***, int32_t *);
} GeneratorClass;
extern const class_t *Generator;
#endif
