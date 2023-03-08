/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/tree.h"

leaf_t *tree_create_leaf(TreeClass *self, node_t *node)
{
    leaf_t *leaf = NULL;
    if (!((leaf = self->alloc(self)))) {
        return NULL;
    }
    return ({ leaf->left = leaf->right = NULL, leaf->node = node, leaf; });
}

void tree_insert_leaf(TreeClass *self, node_t *value)
{
    leaf_t *current = self->root, *parent = NULL;

    if (self->root == NULL) {
        self->root = self->create_leaf(self, value);
        return;
    }
    while (current) {
        parent = current;
        if (value->costs.h < current->node->costs.h) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (value->costs.h < parent->node->costs.h) {
        parent->left = self->create_leaf(self, value);
    } else {
        parent->right = self->create_leaf(self, value);
    }
}

leaf_t *tree_get_leaf(TreeClass *self, node_t *value)
{
    leaf_t *current = self->root;

    if (self->root == NULL) {
        return NULL;
    }
    while (current) {
        if (memcmp(&value->coords, &current->node->coords, sizeof(coords_t))
            == 0) {
            return current;
        }
        if (value->costs.h < current->node->costs.h) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current;
}

leaf_t *tree_get_smallest(leaf_t *root)
{
    leaf_t *current = root;

    if (current == NULL) {
        return NULL;
    }

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}
