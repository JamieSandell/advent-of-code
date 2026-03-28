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
       
        char batteries_turned_on_joltage_raw[MAX_BATTERIES_TURN_ON];
        int current_search_start = 0;
        int total_skips_allowed = battery_bank_length - MAX_BATTERIES_TURN_ON;

        // Sliding window
        for (int i = 0; i < MAX_BATTERIES_TURN_ON; ++i)
        {
            int highest_joltage = -1;
            int best_index = current_search_start;
            int search_end = current_search_start + total_skips_allowed;

            for (int j = current_search_start; j <= search_end; ++j)
            {
                int value = token[j] - '0';                

                if (value > highest_joltage)
                {
                    highest_joltage = value;
                    best_index = j;

                    if (value == 9) // can't get higher
                    {
                        break;
                    }
                }
            }

            batteries_turned_on_joltage_raw[i] = token[best_index];
            total_skips_allowed -= best_index - current_search_start;
            current_search_start = best_index + 1;            
        }
        
        answer_two += atoll(batteries_turned_on_joltage_raw);
        token = strtok(NULL, "\n");
    }

    fprintf(stdout, "\nMaximum joltage for part 1 is: %d\n", answer_one);
    fprintf(stdout, "\nMaximum joltage for part 2 is: %" PRId64 "\n", answer_two);

    return EXIT_SUCCESS;
}

// if a is smaller return a positive
int compare_ints(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}