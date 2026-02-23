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
    //int64_t answer_two = 0;

    // 987654321111111
    // 811111111111119
    // 234234234234278
    // 818181911112111
    while (token != NULL)
    {
        //////////////////////// answer one
        int largest_joltage = 0;
        int second_largest_joltage = 0;
        size_t battery_bank_length = strlen(token);

        for (size_t battery_bank_index = 0; battery_bank_index < battery_bank_length - 1; ++battery_bank_index)
        {
            int current_battery_joltage = token[battery_bank_index] - '0';

            if (current_battery_joltage > largest_joltage)
            {
                largest_joltage = current_battery_joltage;
                second_largest_joltage = 0;
            }
            else if(current_battery_joltage > second_largest_joltage)
            {
                second_largest_joltage = current_battery_joltage;
            }
        }

        int last_battery_joltage = token[battery_bank_length - 1] - '0';

        if (last_battery_joltage > second_largest_joltage)
        {
            second_largest_joltage = last_battery_joltage;
        }

        answer_one += ((largest_joltage * 10) + second_largest_joltage);

        //////////////////////// answer two
        int *batteries = malloc(sizeof(int) * battery_bank_length);
        int *battery = batteries;

        for (size_t battery_bank_index = 0; battery_bank_index < battery_bank_length; ++battery_bank_index)
        {
            *battery = token[battery_bank_index] - '0';
            ++battery;
        }

        qsort(batteries, battery_bank_length, sizeof(int), compare_ints);

        for (size_t i = 0; i < battery_bank_length; ++i)
        {
            fprintf(stdout, "%d\n", batteries[i]);
        }

        int number_of_batteries_to_discard = battery_bank_length - MAX_BATTERIES_TURN_ON; // assumes the amount of batteries in a bank is greater than the number to turn on in that bank

        for (size_t battery_bank_index = 0; battery_bank_index < battery_bank_length; ++battery_bank_index)
        {
            if (token[battery_bank_index] - '0' == )
        }

        free(batteries);

        token = strtok(NULL, "\n");
    }

    fprintf(stdout, "\nMaximum joltage for answer 1 is: %d\n", answer_one);

    return EXIT_SUCCESS;
}

// if a is smaller return a positive
int compare_ints(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}