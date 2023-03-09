/*
** EPITECH PROJECT, 2023
** solver.c
** File description:
** dante solver oop definition
*/

#include "../include/oop/solver.h"

void solver_solve_maze(SolverClass *self)
{
    while (self->open->leaf_count > 0) {
        self->smallest = self->open->get_smallest(self->open->root);
        leaf_t *out =
            self->open->remove_leaf(self->open, self->smallest->node);
        self->close->insert_leaf(self->close, out->node);
        if (memcmp(&self->smallest->node->coords, &self->target->coords,
                sizeof(self->target->coords))
            == 0)
            self->print_maze(self, out, self->smallest);
        self->get_adjacent(self, &self->smallest->node->coords);
        self->prune_adjacent(self);
        self->open->free(self->open, out);
    }
    write(STDOUT_FILENO, "no solution found", 17);
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
        *(string + i) == '\n' ? offset++ : ({
            *(self->data + i - offset) = self->pool + i - offset;
            ASSERT((*(string + i) == '*' || *(string + i) == 'X'), self);
            node = *(self->data + i - offset);
            node->walkable = *(string + i) == '*';
            node->costs.g = INT16_MAX;
            node->costs.h = INT16_MAX;
            node->costs.f = node->costs.h + node->costs.g;
            node->coords.x = (i - offset) % self->columns;
            node->coords.y = (i - offset) / self->columns;
        });
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

// TODO(jabolo): check that you can move 4 ways
bool solver_is_valid(SolverClass *self)
{
    char *str = (char *) self->addr;
    size_t rows = (self->size - self->offset) / self->columns;

    ASSERT(self->columns != rows, self);
    ASSERT(*str == '*', self);
    ASSERT(*(str + self->size - 1) == '*', self);
    for (size_t i = 0; i < rows - 1; i++) {
        ASSERT(*(str + ((self->columns * (i + 1)) + i)) == '\n', self);
    }
    return !self->error;
}
