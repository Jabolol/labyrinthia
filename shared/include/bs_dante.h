/*
** EPITECH PROJECT, 2023
** bs_dante.h
** File description:
** bs bs_dante header file
*/

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#ifndef __DANTE_1
    #define __DANTE_1
typedef struct node node_t;
typedef struct node {
    bool walkable;
    struct {
        int32_t x;
        int32_t y;
    } coords;
    struct {
        int32_t f;
        int32_t g;
        int32_t h;
    } costs;
    node_t *parent;
} node_t;
char **split(char *const readonly_str, bool (*fn)(char const c));
void cleanup_split(char ***ptr);
void free_class(void *ptr);
#endif
