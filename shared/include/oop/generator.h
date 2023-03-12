/*
** EPITECH PROJECT, 2023
** solver.h
** File description:
** dante solver header file
*/

#include "./stack.h"
#include "oop.h"
#include "../bs_dante.h"

#ifndef __DANTE_GENERATOR
    #define __DANTE_GENERATOR
typedef struct {
    size_t x;
    size_t y;
    int8_t x_dir;
    int8_t y_dir;
    bool _condition;
} neighbour_t;
typedef struct generator_aux GeneratorClass;
typedef struct generator_aux {
    /* Inheritance */
    class_t parent;
    /* Properties */
    size_t width;
    bool is_perfect;
    StackClass *stack;
    size_t height;
    size_t total;
    cell_t ***grid;
    cell_t *chunk;
    /* Methods */
    void (*get_neighbours)(GeneratorClass *, cell_t *, cell_t ***, int32_t *);
    void (*add_neighbour)(
        GeneratorClass *, neighbour_t *, cell_t ***, size_t *);
    void (*print_grid)(GeneratorClass *);
    void (*visit_neighbour)(GeneratorClass *, cell_t ***, int32_t);
    void (*backtrack)(GeneratorClass *);
    void (*free_neighbours)(cell_t ***);
    void (*generate_maze)(GeneratorClass *self);
} GeneratorClass;
void generator_backtrack(GeneratorClass *);
void generator_free_neighbours(cell_t ***);
void generator_generate_maze(GeneratorClass *);
void generator_visit_neighbour(GeneratorClass *, cell_t ***, int32_t);
extern const class_t *Generator;
#endif
