/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/tree.h"

void tree_destructor(void *ptr)
{
    TreeClass *self = (TreeClass *) ptr;
}

leaf_t *tree_create_leaf(node_t *node)
{
    leaf_t *leaf = NULL;
    if (!((leaf = malloc(sizeof(*leaf))))) {
        return NULL;
    }
    leaf->left = leaf->right = NULL;
    leaf->node = node;
    return leaf;
}

void tree_insert_leaf(TreeClass *self, node_t *value)
{
    return;
}

leaf_t *get_smallest(leaf_t *root)
{
    return NULL;
}

leaf_t *tree_remove_leaf(TreeClass *self, leaf_t *root, node_t *node)
{
    return NULL;
}

const TreeClass init_tree = {
    {
        ._size = sizeof(TreeClass),
        ._name = "Tree",
        ._constructor = NULL,
        ._destructor = &tree_destructor,
    },
    .tree = NULL,
    .create_leaf = &tree_create_leaf,
    .get_smallest = &get_smallest,
    .insert_leaf = &tree_insert_leaf,
    .remove_leaf = &tree_remove_leaf,
};

const class_t *Tree = (const class_t *) &init_tree;
