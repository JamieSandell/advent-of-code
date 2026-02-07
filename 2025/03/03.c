#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

int main(void)
{
    char *input = read_entire_file_into_buffer();    
    char *token = strtok(input, "\n");
    int maximum_joltage = 0; 

    while (token != NULL)
    {
        int largest_number = 0;
        int second_largest_number = 0;
        char *c = token;        

        while (*c != '\0')
        {
            int battery = (*c) - '0';
            
            if (battery >= largest_number)
            {
                largest_number = battery;
            }
            else if(battery >= second_largest_number)
            {
                if ((largest_number * 10) + battery > (largest_number * 10) + second_largest_number)
                {
                    second_largest_number = battery;
                }
            }

            ++c;
        }

        maximum_joltage += ((largest_number * 10) + second_largest_number);
        token = strtok(NULL, "\n");
    }

    fprintf(stdout, "\nMaximum joltage is: %d\n", maximum_joltage);

    return EXIT_SUCCESS;
}