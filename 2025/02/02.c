#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"

#define MAX_DIGITS_IN_RANGE 32

void get_range_numbers(const char *range, int64_t *lower, int64_t *upper);
void split_string(const char *string, char **first_string, char **second_string, char delimiter);
void split_string_in_half(const char *string, char **first_half, char **second_half);
int substring_count(const char *string, const char *substring);

int main(void)
{
    char *raw_input = read_entire_file_into_buffer();
    char *range = strtok(raw_input, ",");

    fprintf(stdout, "\n");
    int64_t password_one = 0;
    int64_t password_two = 0;

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

        for (int64_t current_number_in_range = lower; current_number_in_range <= upper; ++current_number_in_range)
        {
            char current_number_in_range_string[MAX_DIGITS_IN_RANGE];
            sprintf(current_number_in_range_string, "%" PRId64, current_number_in_range);
            int range_string_length = strlen(current_number_in_range_string);

            if (range_string_length % 2 != 0)
            {
                continue;
            }

            char *first_half;
            char *second_half;
            split_string_in_half(current_number_in_range_string, &first_half, &second_half);
            
            if (strcmp(first_half, second_half) == 0)
            {
                fprintf(stdout, "%s is an invalid id.\n", current_number_in_range_string);
                password_one += current_number_in_range;
            }
        }

        /*
        loop through the range
            convert the current number in the range to a string
            get the length of the current number string
            loop (i) through the the current number string
                x = current number / i + 1 leaves no remainder
                first_x_characters = get first x characters of current number string
                first_x_characters must be found j times, if it is add it to the password_two count

        Examples:
        12341234 is invalid (1234 two times)
        length equals 8
        8 % 1 equals 0
        8 / 1 equals 8
        so the first 1 characters (1) must be found eight (8 / 1) times to be an invalid id
        it isn't
        8 % 2 equals 0
        8 / 2 equals 4
        so the first 4 characters (1234) must be found twice (8 / 2)
        it is

        11 is invalid (1 two times)
        length equals 2
        2 % 1 equals 0
        2 / 1 equals 2
        so the first 1 characters (1) must be found two (2 / 1) times to be an invald id
        it is

        12 is valid
        length equals 2
        2 % 1 equals 0
        2 / 1 equals 2
        so the first 1 characters (1) must be found two (2 / 1) times to be an invalid id
        it isn't.
        2 % 2 equals 0
        2 / 2 equals 1
        so the first 2 characters (12)
        */

        for (int64_t current_number_in_range = lower; current_number_in_range <= upper; ++current_number_in_range)
        {
            if (current_number_in_range == 100)
            {
                printf("debug: 100\n");
            }

            char current_number_in_range_string[MAX_DIGITS_IN_RANGE];
            sprintf(current_number_in_range_string, "%" PRId64, current_number_in_range);
            size_t current_number_length = strlen(current_number_in_range_string);

            for (size_t i = 1; i < current_number_length; ++i)
            {
                if (current_number_length % i != 0)
                {
                    continue;
                }

                // x = current number / i
                // first_x_characters = get first x characters of current number string
                // first_x_characters must be found x times, if it is add it to the password_two count
                int x = current_number_length / i;

                char *first_x_characters = malloc(i + 1);

                first_x_characters = strncpy(first_x_characters, current_number_in_range_string, i);
                first_x_characters[i] = '\0';
                int first_x_characters_found_count = substring_count(current_number_in_range_string, first_x_characters);

                if (first_x_characters_found_count == x)
                {
                    password_two += current_number_in_range;
                    fprintf(stdout, "%s is an invalid id.\n", current_number_in_range_string);
                    free(first_x_characters);
                    break;
                }

                free(first_x_characters);
            }
        }
        
        range = strtok(NULL, ",");
    }

    fprintf(stdout, "password one is: %" PRId64 "\n", password_one);
    fprintf(stdout, "password two is: %" PRId64 "\n", password_two);

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

    char *lower_string;
    char *upper_string;
    split_string(range, &lower_string, &upper_string, '-');

    fprintf(stdout, "lower range: %s\n", lower_string);
    *lower = atoll(lower_string);
    fprintf(stdout, "upper range: %s\n", upper_string);
    *upper = atoll(upper_string);
}

void split_string(const char *string, char **first_string, char **second_string, char delimiter)
{
    if (string == NULL)
    {
        fprintf(stdout, "Error: string was null\n");
        return;
    }

    char *delimiter_position = strchr(string, delimiter);
    size_t delimiter_index = delimiter_position - string;

    size_t string_length = strlen(string);
    size_t first_string_length = (string_length - 1) / 2; // - 1 to ignore the delimiter.
    *first_string = malloc(first_string_length + 1);
    memcpy(*first_string, string, first_string_length);
    (*first_string)[first_string_length] = '\0';

    size_t second_string_length = (string_length - 1) - first_string_length;
    *second_string = malloc(second_string_length + 1);
    memcpy(*second_string, string + first_string_length + 1, second_string_length); // + 1 to ignore the delimiter.
    (*second_string)[second_string_length] = '\0';
}

void split_string_in_half(const char *string, char **first_half, char **second_half)
{
    size_t string_length = strlen(string);

    if (string_length % 2 != 0)
    {
        fprintf(stderr, "Error: %s is not divisible by 2.\n", string);
        exit(EXIT_FAILURE);
    }

    size_t half_length = string_length / 2;
    *first_half = malloc(half_length + 1);
    memcpy(*first_half, string, half_length);
    (*first_half)[half_length] = '\0';

    *second_half = malloc(half_length + 1);
    memcpy(*second_half, string + half_length, half_length);
    (*second_half)[half_length] = '\0';
}

int substring_count(const char *string, const char *substring)
{
    if (!string || !substring || *substring == '\0')
    {
        return 0;
    }

    const char *temp = string;
    int count = 0;

    while ((temp = strstr(temp, substring)))
    {
        ++count;
        temp += strlen(substring);
    }

    return count;
}
