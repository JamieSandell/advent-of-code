#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

#define MAX_BATTERIES_TURN_ON 12

int compare_ints(const void *a, const void *b);

int main(void)
{
    char *input = read_entire_file_into_buffer();
    fprintf(stdout, "\n");
    char *token = strtok(input, "\n");
    int answer_one = 0; 
    int64_t answer_two = 0;

    while (token != NULL)
    {
        //////////////////////// answer one

        //////////////////////// answer two
		
        token = strtok(NULL, "\n");
    }

    fprintf(stdout, "\n<answer 1 text>: %d\n", answer_one);
    fprintf(stdout, "\n<answer 2 text>: %" PRId64 "\n", answer_two);

    return EXIT_SUCCESS;
}

// if a is smaller return a positive
int compare_ints(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}