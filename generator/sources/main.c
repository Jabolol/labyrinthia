/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include "../include/bs_dante.h"

typedef struct {
    bool visited;
    char key;
} cell_t;

cell_t *get_neighbour(
    cell_t *root, cell_t *cell, coords_t *coords, coords_t *dimensions)
{
    int32_t rows = dimensions->y;
    int32_t cols = dimensions->x;

    cell_t *out = NULL;

    int32_t dx[4] = {0, -2, 0, 2};
    int32_t dy[4] = {-2, 0, 2, 0};

    int32_t i = rand() % 4;

    int32_t nx = coords->x + *(dx + i);
    int32_t ny = coords->y + *(dy + i);

    if (ny >= 0 && ny < rows && nx >= 0 && nx < cols
        && (ny == coords->y || nx == coords->x))
        out = (root + (ny * cols) + nx);

    // return the direction

    return out;
}

int32_t perfect_maze(char *path, int32_t x, int32_t y)
{
    srand(time(NULL));
    //
    int32_t fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Couldn't open %s\n", path);
        exit(EXIT_ERROR);
    }
    const size_t size = lseek(fd, 0, SEEK_END);
    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "Failed mmap allocation\n");
        exit(EXIT_ERROR);
    }
    close(fd);
    //

    cell_t *cells = calloc((size + y - 1), sizeof(*cells));

    size_t max_cells = (size + y - 1), visited_cells = 0;

    for (size_t i = 0; i < size; i += y) {
        (cells + i)->visited = ((((cells + i)->key = '\n')));
    }

    cell_t *current = cells;
    cell_t *neighbour = NULL;

    while (visited_cells < max_cells) {
        if (!((neighbour = get_neighbour(cells, current,
                   &(coords_t){
                       .x = (current - cells) - (x * ((current - cells) / x)),
                       .y = ((current - cells) / y) + 1,
                   },
                   &(coords_t){.x = x, .y = y})))) {
            continue;
        }
        if (!neighbour->visited) {
            // set visited
            neighbour->visited = true;
        }
        current = neighbour;
        visited_cells += 1;
    }

    // print the solution

    free(cells);
    //
    munmap(addr, size);
    //
    return 0;
}

int main(int argc, char **argv)
{
    /*
        OOOOOXOXX
        OXOXXXOXX
        OXOOOOOXX
        XXXXOXXXX
        XXOOOOOOO
    */
    // TODO(jabolo): Implement error handling

    // ./solver x y <perfect>
    return perfect_maze(*(argv + 1), atoi(*(argv + 2)), atoi(*(argv + 3)));
}
