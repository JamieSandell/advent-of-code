#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

int main(void)
{
    char *input = read_entire_file_into_buffer();
    
    char *token = strtok(input, "\n");

    while (token != NULL)
    {
        fprintf(stdout, "%s\n", token);
        token = strtok(NULL, "\n");
    }

    return EXIT_SUCCESS;
}