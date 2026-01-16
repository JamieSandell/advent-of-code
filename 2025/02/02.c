#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

void get_range_numbers(const char *range, int64_t *lower, int64_t *upper);

int main(void)
{
    char *raw_input = read_entire_file_into_buffer();
    char *range = strtok(raw_input, ",");

    fprintf(stdout, "\n");
    int64_t password = 0;

    while (range != NULL)
    {
        fprintf(stdout, "range: %s\n", range);

        int64_t lower;
        int64_t upper;
        get_range_numbers(range, &lower, &upper);

        /*
        loop through the range
        convert the current number to a string
        if the length of the string is not divisible by 2 then skip
        else divide the string into two, compare the two strings, if equal then invalid input

        e.g. range 10 - 11
        "10" is divisible by 2, split it, so a = "1", b = "0", not equal so skip
        "11" is divisible by 2, split it, so a = "1", b = "1", they are equal so add to the password integer.
        */        

        for (int64_t i = lower; i <= upper; ++i)
        {
            char i_string[11];
            sprintf(i_string, "%ld", i);
            int i_string_length = strlen(i_string);

            if (i_string_length % 2 != 0)
            {
                continue;
            }

            int half_i_string_length = i_string_length / 2;
            char *left = malloc(sizeof(char) * half_i_string_length + 1);
            memcpy(left, i_string, half_i_string_length);
            left[half_i_string_length] = '\0';
            char *right = malloc(sizeof(char) * half_i_string_length + 1);
            memcpy(right, i_string + half_i_string_length, half_i_string_length);
            right[half_i_string_length] = '\0';
            
            if (strcmp(left, right) == 0)
            {
                fprintf(stdout, "%s is an invalid id.\n", i_string);
                password += i;
            }
        }

        range = strtok(NULL, ",");
    }

    fprintf(stdout, "password is: %ld", password);

    return EXIT_SUCCESS;
}

void get_range_numbers(const char *range, int64_t *lower, int64_t *upper)
{
    const char *c = range;
    int lower_char_count = 0;

    while(*c != '-')
    {
        ++lower_char_count;
        ++c;
    }

    char *lower_string = malloc(sizeof(char) * lower_char_count + 1);
    strncpy(lower_string, range, lower_char_count);
    lower_string[lower_char_count] = '\0';
    fprintf(stdout, "lower range: %s\n", lower_string);
    *lower = atol(lower_string);

    int upper_char_count = strlen(range) - lower_char_count - 1;
    char *upper_string = malloc(sizeof(char) * upper_char_count + 1);
    const char *upper_string_start = &range[lower_char_count + 1];
    strncpy(upper_string, upper_string_start, upper_char_count);
    upper_string[upper_char_count] = '\0';
    fprintf(stdout, "upper range: %s\n", upper_string);
    *upper = atol(upper_string);
}