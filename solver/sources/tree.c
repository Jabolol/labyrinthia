/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/tree.h"

leaf_t *tree_create_leaf(node_t *node)
{
    leaf_t *leaf = NULL;
    if (!((leaf = malloc(sizeof(*leaf))))) {
        return NULL;
    }
    return ({ leaf->left = leaf->right = NULL, leaf->node = node, leaf; });
}

void tree_insert_leaf(TreeClass *self, node_t *value)
{
    leaf_t *current = self->root;
    leaf_t *parent = NULL;

    if (self->root == NULL) {
        self->root = self->create_leaf(value);
        self->leaf_count += 1;
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

    self->leaf_count += 1;
    if (value->costs.h < parent->node->costs.h) {
        parent->left = self->create_leaf(value);
    } else {
        parent->right = self->create_leaf(value);
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

    if (!current) {
        return current;
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

leaf_t *tree_remove_leaf(TreeClass *self, node_t *value)
{
    leaf_t *parent = NULL;
    leaf_t *current = self->root;
    struct {
        int left : 2;
        int right : 2;
    } flag = {0, 0};

    while (current) {
        if (!memcmp(&value->coords, &current->node->coords, sizeof(coords_t)))
            break;
        parent = current;
        if (value->costs.h < current->node->costs.h) {
            current = current->left;
            flag.right = !((flag.left = 1));
        } else {
            current = current->right;
            flag.left ^= flag.right ^= ((flag.right = flag.left));
        }
    }

    if (current == NULL) {
        return NULL;
    }

    if (!current->left && !current->right) {
        if (current == self->root) {
            self->root = NULL;
        } else {
            flag.left ? (parent->left = NULL) : ((parent->right = NULL));
        }
        self->leaf_count -= 1;
        return current;
    }

    if (!!current->left != !!current->right) {
        if (current == self->root) {
            self->root = flag.left ? current->left : current->right;
        } else {
            leaf_t *child = current->left ? current->left : current->right;
            flag.left ? (parent->left = child) : ((parent->right = child));
        }
        self->leaf_count -= 1;
        return current;
    }

    if (current->left && current->right) {
        leaf_t *new_root = current->left;
        leaf_t *right = current->right;
        while (new_root->right) {
            new_root = new_root->right;
        }
        new_root->right = right;
        self->root == current ? (self->root = current->left)
            : flag.left       ? (parent->left = current->left)
                              : ((parent->right = current->left));
        self->leaf_count -= 1;
        return current;
    }

    __builtin_unreachable();
    return current;
}

const TreeClass init_tree = {
    {
        ._size = sizeof(TreeClass),
        ._name = "Tree",
        ._constructor = NULL,
        ._destructor = NULL,
    },
    .root = NULL,
    .leaf_count = 0,
    .create_leaf = &tree_create_leaf,
    .get_smallest = &tree_get_smallest,
    .insert_leaf = &tree_insert_leaf,
    .remove_leaf = &tree_remove_leaf,
    .get_leaf = &tree_get_leaf,
};

const class_t *Tree = (const class_t *) &init_tree;
