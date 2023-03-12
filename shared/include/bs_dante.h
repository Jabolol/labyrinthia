/*
** EPITECH PROJECT, 2023
** bs_dante.h
** File description:
** bs bs_dante header file
*/

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#ifndef __DANTE_1
    #define __DANTE_1
    #define EXIT_ERROR            84
    #define MANHATTAN(start, end) abs(start.x - end.x) + abs(start.y - end.y)
    #define ASSERT(x, s)                                                      \
        ({                                                                    \
            if (!((*s).error) && !(x)) {                                      \
                fprintf(stderr,                                               \
                    "Assertion failed: %s, function %s, file %s, line %d.\n", \
                    #x, __func__, __FILE__, __LINE__);                        \
                (*s).error = true;                                            \
            }                                                                 \
        })

typedef struct {
    int32_t x;
    int32_t y;
} coords_t;
typedef struct node node_t;
typedef struct node {
    bool walkable;
    coords_t coords;
    struct {
        double f;
        double g;
        double h;
    } costs;
    node_t *parent;
} node_t;
char **split(char *const readonly_str, bool (*fn)(char const c));
void cleanup_split(char ***ptr);
void free_class(void *ptr);
#endif
