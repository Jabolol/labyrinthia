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
    self->tree = new_class(Tree);
}

void solver_destructor(void *ptr)
{
    SolverClass *self = (SolverClass *) ptr;
    destroy_class(self->tree);
    munmap(self->addr, self->size);
    free(self->pool);
    free(self->data);
}

void solver_load_path(SolverClass *self, char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Couldn't open %s\n", path);
        exit(EXIT_FAILURE);
    }
    self->size = lseek(fd, 0, SEEK_END);
    self->addr = mmap(NULL, self->size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (self->addr == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "Failed mmap allocation\n");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void solver_load_nodes(SolverClass *self)
{
    if (!((self->pool = malloc(self->size * sizeof(node_t))))) {
        fprintf(stderr, "Failed malloc allocation\n");
        exit(EXIT_FAILURE);
    }
    if (!((self->data = malloc(self->size * sizeof(node_t *))))) {
        fprintf(stderr, "Failed malloc allocation\n");
        exit(EXIT_FAILURE);
    }
    char *string = (char *) self->addr;
    self->columns = (strchr(string, '\n') - string) + 1;
    node_t *node = NULL;

    for (size_t i = 0; i < self->size; i++) {
        node = *(self->data + i) = self->pool + i;
        node->walkable = *(string + i) == '*';
        node->costs.f = node->costs.g = node->costs.h = INT32_MAX;
        node->coords.x = i % self->columns;
        node->coords.y = i / self->columns;
    }
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
    .size = 0,
    .columns = 0,
    .load_file = &solver_load_path,
    .load_nodes = &solver_load_nodes,
};

const class_t *Solver = (const class_t *) &init_solver;
