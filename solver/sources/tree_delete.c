/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/tree.h"

void tree_traverse_tree(
    leaf_t **current, leaf_t **parent, node_t *value, flag_t *flag)
{
    while (*current) {
        if (!memcmp(
                &value->coords, &(*current)->node->coords, sizeof(coords_t)))
            break;
        *parent = *current;
        if (value->costs.h < (*current)->node->costs.h) {
            (*current) = (*current)->left;
            flag->right = !((flag->left = 1));
        } else {
            (*current) = (*current)->right;
            flag->right = flag->left, flag->left ^= flag->right;
        }
    }
}

leaf_t *tree_remove_no_child(
    TreeClass *self, leaf_t *current, leaf_t *parent, flag_t *flag)
{
    if (!current->left && !current->right) {
        if (current == self->root) {
            self->root = NULL;
        } else {
            flag->left ? (parent->left = NULL) : ((parent->right = NULL));
        }
        self->leaf_count -= 1;
        return current;
    }
    return NULL;
}

leaf_t *tree_remove_one_child(
    TreeClass *self, leaf_t *current, leaf_t *parent, flag_t *flag)
{
    if (!!current->left != !!current->right) {
        if (current == self->root) {
            self->root = flag->left ? current->left : current->right;
        } else {
            leaf_t *child = current->left ? current->left : current->right;
            flag->left ? (parent->left = child) : ((parent->right = child));
        }
        self->leaf_count -= 1;
        return current;
    }
    return NULL;
}

leaf_t *tree_remove_two_children(
    TreeClass *self, leaf_t *current, leaf_t *parent, flag_t *flag)
{
    if (current->left && current->right) {
        leaf_t *new_root = current->left, *right = current->right;
        while (new_root->right)
            new_root = new_root->right;
        new_root->right = right;
        (self->root == current) ? (self->root = current->left) : ({
            if (flag->left) {
                parent->left = current->left;
            } else
                parent->right = current->left;
        });
        self->leaf_count -= 1;
        return current;
    }
    return NULL;
}

leaf_t *tree_remove_leaf(TreeClass *self, node_t *value)
{
    leaf_t *parent = NULL, *current = self->root, *out = NULL;
    flag_t flag = {0, 0};

    self->traverse_tree(&current, &parent, value, &flag);

    if (current == NULL) {
        return NULL;
    }
    if (((out = self->remove_no_child(self, current, parent, &flag)))) {
        return out;
    }
    if (((out = self->remove_one_child(self, current, parent, &flag)))) {
        return out;
    }
    if (((out = self->remove_two_children(self, current, parent, &flag)))) {
        return out;
    }
    __builtin_unreachable();
    return current;
}
