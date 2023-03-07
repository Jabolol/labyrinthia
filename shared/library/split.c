/*
** EPITECH PROJECT, 2023
** split.c
** File description:
** split a string into an array
*/

#include "../include/bs_dante.h"

char **split(char *const readonly_str, bool (*fn)(char c))
{
    char *string = strdup(readonly_str);
    int32_t len = strlen(string);
    int32_t delim_len = 0;
    char **split_string = NULL;

    for (int32_t i = 0; i < len; i++)
        if (fn(*(string + i))) {
            delim_len += 1;
            *(string + i) = '\0';
        }
    if (!(split_string = malloc(delim_len + 2 * sizeof(char *))))
        return NULL;
    for (int32_t i = 0; i < delim_len + 1; i++) {
        int32_t substr_len = strlen(string) + 1;
        *(split_string + i) = string;
        string = string + substr_len;
    }
    *(split_string + delim_len + 1) = NULL;
    return split_string;
}

// `__attribute__((cleanup(cleanup_split)))`
void cleanup_split(char ***ptr)
{
    if (*ptr) {
        free(**ptr);
        free(*ptr);
    }
}
