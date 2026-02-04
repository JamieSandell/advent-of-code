#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

// caller is responsible for the lifecycle of buffer
char *read_entire_file_into_buffer(void)
{
    FILE *input_file = fopen("input.txt", "r");

    if (input_file == NULL)
    {
        fprintf(stderr, "Error: failed to open input.txt for reading.\n");
        exit(EXIT_FAILURE);
    }

    fseek(input_file, 0L, SEEK_END);
    size_t input_file_size = ftell(input_file);
    fseek(input_file, 0L, SEEK_SET);
    char *buffer = calloc(input_file_size + 1, sizeof(char));

    if (buffer == NULL)
    {
        fprintf(stderr, "Error: failed to allocate memory for buffer.\n");
        exit(EXIT_FAILURE);
    }

    size_t bytes_read = fread(buffer, sizeof(char), input_file_size, input_file);
    fclose(input_file);
    buffer[bytes_read] = '\0';
    fprintf(stdout, "Info: contents of input.txt\n\n%s", buffer);

    return buffer;
}