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
        exit(EXIT_ERROR);
    }
}

void tree_destructor(void *ptr)
{
    TreeClass *self = (TreeClass *) ptr;
    free(self->pool);
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
    .remove_no_child = &tree_remove_no_child,
    .remove_one_child = &tree_remove_one_child,
    .remove_two_children = &tree_remove_two_children,
    .traverse_tree = &tree_traverse_tree,
};

const class_t *Tree = (const class_t *) &init_tree;
