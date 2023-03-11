/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** project entrypoint
*/

#include <time.h>
#include "../include/bs_dante.h"

// TBD
int32_t perfect_maze(int32_t x, int32_t y)
{
    srand(time(NULL));
    return 0;
}

int main(int argc, char **argv)
{
    return perfect_maze(atoi(*(argv + 1)), atoi(*(argv + 2)));
}
