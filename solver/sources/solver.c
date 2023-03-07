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
    self->open = new_class(Tree, self->size - self->offset);
    self->close = new_class(Tree, self->size - self->offset);
}

void solver_destructor(void *ptr)
{
    SolverClass *self = (SolverClass *) ptr;
    destroy_class(self->open);
    destroy_class(self->close);
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
    self->addr =
        mmap(NULL, self->size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (self->addr == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "Failed mmap allocation\n");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void solver_load_nodes(SolverClass *self)
{
    if (!((self->pool = calloc(self->size + 1, sizeof(node_t))))) {
        fprintf(stderr, "Failed calloc allocation\n");
        exit(EXIT_FAILURE);
    }
    if (!((self->data = calloc(self->size + 1, sizeof(node_t *))))) {
        fprintf(stderr, "Failed calloc allocation\n");
        exit(EXIT_FAILURE);
    }
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

node_t **solver_get_adjacent(SolverClass *self, coords_t *coords)
{
    node_t **neighbors = NULL;

    if (!((neighbors = calloc(4, sizeof(node_t *))))) {
        return NULL;
    }
    int32_t dx[4] = {0, -1, 0, 1};
    int32_t dy[4] = {-1, 0, 1, 0};

    for (int32_t i = 0; i < 4; i++) {
        int32_t nx = coords->x + dx[i];
        int32_t ny = coords->y + dy[i];
        if ((ny * self->columns) + nx > 0
            && (ny * self->columns) + nx < self->size - self->offset) {
            *(neighbors + i) = *(self->data + (ny * self->columns) + nx);
        } else {
            *(neighbors + i) = NULL;
        }
    }
    return neighbors;
}

double solver_get_distance(coords_t *start, coords_t *end)
{
    return sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2));
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
    .offset = 0,
    .load_file = &solver_load_path,
    .load_nodes = &solver_load_nodes,
    .get_adjacent = &solver_get_adjacent,
    .get_distance = &solver_get_distance,
};

const class_t *Solver = (const class_t *) &init_solver;
