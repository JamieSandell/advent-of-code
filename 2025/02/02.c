#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

void get_range_numbers(const char *range, int64_t *lower, int64_t upper);

int main(void)
{
    char *raw_input = read_entire_file_into_buffer();
    char *range = strtok(raw_input, ",");

    fprintf(stdout, "\n");

    while (range != NULL)
    {
        fprintf(stdout, "range: %s\n", range);

        int64_t lower;
        int64_t upper;
        get_range_numbers(range, &lower, &upper);

        range = strtok(NULL, ",");
    }

    return EXIT_SUCCESS;
}

void get_range_numbers(const char *range, int64_t *lower, int64_t upper)
{
    char *c = range;
    int count = 0;

    while(*c != '-')
    {
        ++count;
        ++c;
    }

    char *lower_string = malloc(sizeof(char) * count + 1);
    strncpy(lower_string, range, count);
    lower_string[count] = '\0';

    char *upper_string = malloc(sizeof(char) * (strlen(range) - count - 1));
}