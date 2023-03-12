/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include "../include/oop/generator.h"
#include "../include/oop/stack.h"
#include "../include/bs_dante.h"

int main(int argc, char **argv)
{
    if (argc < 3 || (atoi(argv[1]) < 1) || (atoi(argv[2]) < 1)
        || (argc == 4 && strcmp(*(argv + 3), "perfect") != 0)) {
        fprintf(stderr, "Usage: %s <width> <height> [perfect]\n", *argv);
        return EXIT_FAILURE;
    }
    GeneratorClass *self = new_class(Generator, atoi(argv[1]), atoi(argv[2]));
    self->is_perfect = (argc == 4 && strcmp(*(argv + 3), "perfect") == 0);
    self->generate_maze(self);
    self->print_grid(self);
    destroy_class(self);
    return EXIT_SUCCESS;
}
