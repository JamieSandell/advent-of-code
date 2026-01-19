#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

void get_range_numbers(const char *range, int64_t *lower, int64_t *upper);

int main(void)
{
    char *raw_input = read_entire_file_into_buffer();
    char *next_token = NULL;
    char *range = strtok_s(raw_input, ",", &next_token);

    fprintf(stdout, "\n");
    int64_t password_one = 0;

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
            sprintf_s(i_string, sizeof(i_string) / sizeof(i_string[0]), "%lld", i);
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
                password_one += i;
            }
        }

        /*
        loop through the range
        convert the number to a string
        get the length of the number
        loop through the length of the number
        if the length of the number is not divisible by the current index then skip
        if the current index is the length of the number then skip
        otherwise check the characters up to the index repeat n times
        if it does it is invalid so add to the password count and break from the inner loop

        999 is invalid
        length equals 3
        3 % 1 equals 0
        3 / 1 equals 3
        so 9 must be found three times to be an invalid id

        1010 is invalid
        length equals 4
        4 % 1 equals 0
        4 / 1 equals 4
        so 1 must be be found four times to be an invalid id, it is not

        4 % 2 equals 0
        4 / 2 equals 2
        so 10 must be found twice to be an invalid id and it is.
        */

        range = strtok_s(NULL, ",", &next_token);
    }

    fprintf(stdout, "password one is: %lld", password_one);

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

    size_t lower_string_size = sizeof(char) * lower_char_count + 1;
    char *lower_string = malloc(lower_string_size);
    strncpy_s(lower_string, lower_string_size, range, lower_char_count);
    lower_string[lower_char_count] = '\0';
    fprintf(stdout, "lower range: %s\n", lower_string);
    *lower = atol(lower_string);

    int upper_char_count = strlen(range) - lower_char_count - 1;
    size_t upper_string_size = sizeof(char) * upper_char_count + 1;
    char *upper_string = malloc(upper_string_size);
    const char *upper_string_start = &range[lower_char_count + 1];
    strncpy_s(upper_string, upper_string_size, upper_string_start, upper_char_count);
    upper_string[upper_char_count] = '\0';
    fprintf(stdout, "upper range: %s\n", upper_string);
    *upper = atol(upper_string);
}
