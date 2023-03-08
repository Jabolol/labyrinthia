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
typedef struct {
    int32_t left : 2;
    int32_t right : 2;
} flag_t;
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
    leaf_t *(*remove_no_child)(TreeClass *, leaf_t *, leaf_t *, flag_t *);
    leaf_t *(*remove_one_child)(TreeClass *, leaf_t *, leaf_t *, flag_t *);
    leaf_t *(*remove_two_children)(TreeClass *, leaf_t *, leaf_t *, flag_t *);
    void (*traverse_tree)(leaf_t **, leaf_t **, node_t *, flag_t *);
    void (*free)(TreeClass *, leaf_t *);
} TreeClass;

void tree_traverse_tree(leaf_t **, leaf_t **, node_t *, flag_t *);
leaf_t *tree_remove_no_child(TreeClass *, leaf_t *, leaf_t *, flag_t *);
leaf_t *tree_remove_one_child(TreeClass *, leaf_t *, leaf_t *, flag_t *);
leaf_t *tree_remove_two_children(TreeClass *, leaf_t *, leaf_t *, flag_t *);
leaf_t *tree_remove_leaf(TreeClass *, node_t *);
leaf_t *tree_create_leaf(TreeClass *, node_t *);
void tree_insert_leaf(TreeClass *, node_t *);
leaf_t *tree_get_leaf(TreeClass *, node_t *);
leaf_t *tree_get_smallest(leaf_t *);
extern const class_t *Tree;
#endif
