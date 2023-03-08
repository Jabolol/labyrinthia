/*
** EPITECH PROJECT, 2023
** solver.h
** File description:
** dante solver header file
*/

#include "oop.h"
#include "../bs_dante.h"

#ifndef __DANTE_TREE
    #define __DANTE_TREE
typedef struct leaf leaf_t;
typedef struct leaf {
    node_t *node;
    leaf_t *left;
    leaf_t *right;
} leaf_t;
typedef struct tree_aux TreeClass;
typedef struct tree_aux {
    /* Inheritance */
    class_t parent;
    /* Properties */
    leaf_t *root;
    size_t leaf_count;
    size_t max_leaves;
    leaf_t *pool;
    /* Methods */
    leaf_t *(*create_leaf)(TreeClass *self, node_t *);
    void (*insert_leaf)(TreeClass *, node_t *);
    leaf_t *(*get_smallest)(leaf_t *);
    leaf_t *(*get_leaf)(TreeClass *self, node_t *value);
    leaf_t *(*remove_leaf)(TreeClass *, node_t *);
    leaf_t *(*alloc)(TreeClass *);
    void (*free)(TreeClass *, leaf_t *);
} TreeClass;
extern const class_t *Tree;
#endif
