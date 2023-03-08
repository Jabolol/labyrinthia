/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/solver.h"

void solver_constructor(void *ptr, va_list __attribute__((unused)) * ap)
{
    SolverClass *self = (SolverClass *) ptr;
    if (!((self->adjacent = calloc(4, sizeof(node_t *))))) {
        fprintf(stderr, "Failed calloc allocation\n");
        exit(EXIT_ERROR);
    }
}

void solver_destructor(void *ptr)
{
    SolverClass *self = (SolverClass *) ptr;
    destroy_class(self->open);
    destroy_class(self->close);
    munmap(self->addr, self->size);
    free(self->pool);
    free(self->data);
    free(self->adjacent);
}

void solver_load_path(SolverClass *self, char *path)
{
    int32_t fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Couldn't open %s\n", path);
        exit(EXIT_ERROR);
    }
    self->size = lseek(fd, 0, SEEK_END);
    self->addr =
        mmap(NULL, self->size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (self->addr == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "Failed mmap allocation\n");
        exit(EXIT_ERROR);
    }
    close(fd);
}

void solver_fill_nodes(SolverClass *self)
{
    char *string = (char *) self->addr;
    self->columns = (strchr(string, '\n') - string);
    node_t *node = NULL;
    int32_t offset = 0;

    for (size_t i = 0; i < self->size; i++) {
        if (*(string + i) == '\n') {
            offset++;
            continue;
        }
        *(self->data + i - offset) = self->pool + i - offset;
        node = *(self->data + i - offset);
        node->walkable = *(string + i) == '*';
        node->costs.g = INT16_MAX;
        node->costs.h = INT16_MAX;
        node->costs.f = node->costs.f + node->costs.g;
        node->coords.x = (i - offset) % self->columns;
        node->coords.y = (i - offset) / self->columns;
    }
    self->offset = offset;
}

void solver_load_nodes(SolverClass *self)
{
    if (!((self->pool = calloc(self->size + 1, sizeof(node_t))))) {
        fprintf(stderr, "Failed calloc allocation\n");
        exit(EXIT_ERROR);
    }
    if (!((self->data = calloc(self->size + 1, sizeof(node_t *))))) {
        fprintf(stderr, "Failed calloc allocation\n");
        exit(EXIT_ERROR);
    }
    self->fill_nodes(self);
    self->open = new_class(Tree, self->size - self->offset);
    self->close = new_class(Tree, self->size - self->offset);
}

const SolverClass init_solver = {
    {
        ._size = sizeof(SolverClass),
        ._name = "Solver",
        ._constructor = &solver_constructor,
        ._destructor = &solver_destructor,
    },
    .addr = NULL,
    .data = NULL,
    .pool = NULL,
    .adjacent = NULL,
    .smallest = NULL,
    .target = NULL,
    .size = 0,
    .columns = 0,
    .offset = 0,
    .load_file = &solver_load_path,
    .load_nodes = &solver_load_nodes,
    .get_adjacent = &solver_get_adjacent,
    .start_solver = &solver_start_solver,
    .prune_adjacent = &solver_prune_adjacent,
    .handle_valid_adjacent = &solver_handle_valid_adjacent,
    .print_maze = &solver_print_maze,
    .fill_nodes = &solver_fill_nodes,
};

const class_t *Solver = (const class_t *) &init_solver;
