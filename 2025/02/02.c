#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_handling.h"

int main(void)
{
    char *raw_input;
    read_entire_file_into_buffer(raw_input);

    return EXIT_SUCCESS;
}