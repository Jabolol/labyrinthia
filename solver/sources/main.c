/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/solver.h"
#include "../include/bs_dante.h"

// TODO(jabolo): Cleanup this code :)
int main(int argc, char **argv)
{
    if (argc != 2) {
        // TODO(jabolo): check file exists, is a maze ...
        return 84;
    }
    SolverClass *self __attribute__((cleanup(free_class))) = new_class(Solver);
    self->load_file(self, *(argv + 1));
    self->load_nodes(self);

    self->open = new_class(Tree, self->size - self->offset);
    self->close = new_class(Tree, self->size - self->offset);

    node_t *target = *(self->data + self->size - self->offset - 1);

    self->open->insert_leaf(self->open, *self->data);

    while (self->open->leaf_count > 0) {
        leaf_t *smallest = self->open->get_smallest(self->open->root);
        leaf_t *out = self->open->remove_leaf(self->open, smallest->node);
        self->close->insert_leaf(self->close, out->node);

        if (memcmp(&smallest->node->coords, &target->coords,
                sizeof(target->coords))
            == 0) {
            node_t *curr = smallest->node;
            while (curr) {
                *((char *) self->addr + (curr->coords.y * self->columns)
                    + curr->coords.x + curr->coords.y) = 'o';
                curr = curr->parent;
            }
            self->open->free(self->open, out);
            write(STDOUT_FILENO, (char *) self->addr, self->size);
            return 0;
        }

        self->get_adjacent(self, &smallest->node->coords);

        for (int8_t i = 0; i < 4; i++) {
            if (!*(self->adjacent + i)) {
                continue;
            }
            if (!(*(self->adjacent + i))->walkable
                || self->close->get_leaf(self->close, (*(self->adjacent + i)))
                    != NULL) {
                continue;
            }
            double g = self->get_distance(
                &(*(self->adjacent + i))->coords, &(*self->data)->coords);
            double h = self->get_distance(
                &(*(self->adjacent + i))->coords, &target->coords);
            double f = g + h;

            if (self->open->get_leaf(self->open, *(self->adjacent + i)) == NULL
                || h < (*(self->adjacent + i))->costs.h) {
                (*(self->adjacent + i))->parent = smallest->node;
                (*(self->adjacent + i))->costs.f = f;
                (*(self->adjacent + i))->costs.g = g;
                (*(self->adjacent + i))->costs.h = h;
                if (self->open->get_leaf(self->open, *(self->adjacent + i))
                    == NULL) {
                    self->open->insert_leaf(self->open, *(self->adjacent + i));
                }
            }
        }

        self->open->free(self->open, out);
    }

    write(STDOUT_FILENO, "no solution found", 17);

    return 84;
}
