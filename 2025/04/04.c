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
        /*
        234234234234278, 15 characters, we need 12, so need to discard (or not turn on 3 of these).
        Can't move batteries, so find the index of the highest number that leaves at least 11 numbers,
        so highest number in the first 4 digits.
        This would be 4, so that's the first number.
        Then find the second number by starting the search after the 3, so starting at number 2 (index 3),
        need to leave 10 numbers, so search between index 3 and index 4, 3 is the highest (index 4) so turn that on.
        Need another 10 numbers, and there's only 10 numbers left, so turn them all on, which gives
        434234234278
        */
		
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