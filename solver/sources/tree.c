/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/tree.h"

void tree_constructor(void *ptr, va_list *args)
{
    TreeClass *self = (TreeClass *) ptr;
    self->max_leaves = va_arg(*args, size_t);
    if (!((self->pool = calloc(self->max_leaves, sizeof(leaf_t))))) {
        fprintf(stderr, "Failed malloc allocation\n");
        exit(84);
    }
}

void tree_destructor(void *ptr)
{
    TreeClass *self = (TreeClass *) ptr;
    free(self->pool);
}

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
    leaf_t *current = self->root;
    leaf_t *parent = NULL;

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
        int32_t left : 2;
        int32_t right : 2;
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
            flag.right = flag.left, flag.left ^= flag.right;
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
        (self->root == current) ? (self->root = current->left) : ({
            if (flag.left) {
                parent->left = current->left;
            } else
                parent->right = current->left;
        });
        self->leaf_count -= 1;
        return current;
    }

    __builtin_unreachable();
    return current;
}

leaf_t *tree_alloc(TreeClass *self)
{
    if (self->leaf_count >= self->max_leaves) {
        return NULL;
    }
    self->leaf_count += 1;
    for (size_t i = 0; i < self->max_leaves; i++) {
        if (((self->pool + i))->node == NULL) {
            return (self->pool + i);
        }
    }
    return NULL;
}

void tree_free(TreeClass *self, leaf_t *ptr)
{
    if (ptr < self->pool || ptr > self->pool + self->max_leaves) {
        __builtin_unreachable();
    }
    memset(ptr, 0, sizeof(*ptr));
}

const TreeClass init_tree = {
    {
        ._size = sizeof(TreeClass),
        ._name = "Tree",
        ._constructor = &tree_constructor,
        ._destructor = &tree_destructor,
    },
    .root = NULL,
    .leaf_count = 0,
    .max_leaves = 0,
    .create_leaf = &tree_create_leaf,
    .get_smallest = &tree_get_smallest,
    .insert_leaf = &tree_insert_leaf,
    .remove_leaf = &tree_remove_leaf,
    .get_leaf = &tree_get_leaf,
    .alloc = &tree_alloc,
    .free = &tree_free,
};

const class_t *Tree = (const class_t *) &init_tree;
