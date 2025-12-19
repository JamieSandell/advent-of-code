#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct Input
{
    FILE *file;
    char *buffer;
    long bytes_read;
    long file_size;
} Input;

struct Input *read_input(void);

void process_combinations(const char *combinations);

void null_terminate_strings(char *buffer);

int main(void)
{
    for(int i = 0; i < 100; ++i)
    {
        insert_at_end(i);
    }

    make_list_circular();

    //print_list();

    Input* input = read_input();

    null_terminate_strings(input->buffer);

    // char *current_combination = input->buffer;

    // while (*current_combination != '\0')
    // {
    //     printf("%s\n", current_combination);
    //     current_combination += strlen(current_combination) + 1;
    // }

    process_combinations(input->buffer);

    return EXIT_SUCCESS;
}

// assumes the input is a null terminated string, converts newlines into null terminated strings
void null_terminate_strings(char *buffer)
{
    for(; *buffer != '\0'; ++buffer)
    {
        if (*buffer == '\n')
        {
            *buffer = '\0';
        }
    }
}

// assumes input.txt is present
struct Input *read_input(void)
{
    Input *input = malloc(sizeof(Input));

    if(input == NULL)
    {
        printf("Error: Failed to create memory for input.\n");
        exit(EXIT_FAILURE);
    }

    input->file = fopen("input.txt", "r");

    if(input->file == NULL)
    {
        printf("Error: Failed to open input.txt for reading.\n");
        exit(EXIT_FAILURE);
    }

    fseek(input->file, 0L, SEEK_END);
    input->file_size = ftell(input->file);
    fseek(input->file, 0L, SEEK_SET);

    input->buffer = calloc(input->file_size + 1, sizeof(char));

    if (input->buffer == NULL)
    {
        printf("Error: Failed to allocate memory for input->buffer.\n");
        exit(EXIT_FAILURE);
    }

    input->bytes_read = fread(input->buffer, sizeof(char), input->file_size, input->file);
    fclose(input->file);

    input->buffer[input->bytes_read] = '\0';

    printf("contents of input.txt\n\n%s", input->buffer);

    return input;
}

Node *turn_dial_clockwise(Node *current, int x)
{
    for (int i = 0; i < x; ++i)
    {
        current = current->next;
    }

    return current;
}

Node *turn_dial_anti_clockwise(Node *current, int x)
{
    for (int i = 0; i < x; ++i)
    {
        current = current->prev;
    }

    return current;
}

// assumes correct format, e.g. no checking for leading whitespace or non-numeric characters
int convert_string_to_int(char *string)
{
    int i = 0;
    int result = 0;

    while(string[i] >= '0' && string[i] <= '9')
    {
        int digit = string[i] - '0';
        result = result * 10 + digit;
        ++i;
    }

    return result;
}

// assumes a combination number between 0 and 99 has been provided.
Node *set_dial_to_starting_position(Node *current, int destination)
{
    while (current->data != destination)
    {
        current = turn_dial_clockwise(current, 1);
    }

    return current;
}

// assumes 50 is the starting point on the dial and all input is valid (LX, RX, e.g. L15, R1)
// assumes lines end with LF (\n)
void process_combinations(const char *combinations)
{
    Node *current = head;
    current = set_dial_to_starting_position(current, 50);
    printf("Dial has been turned to %d\n", current->data);

    int password = 0;

    const char *current_string = combinations;

    while (*current_string != '\0')
    {
        char direction = current_string[0];
        int turn_amount = atoi(current_string + 1);
        printf("Turning %c %d times\n", direction, turn_amount);

        if (direction == 'R')
        {
            current = turn_dial_clockwise(current, turn_amount);
        }
        else
        {
           current = turn_dial_anti_clockwise(current, turn_amount);
        }

        printf("Dial is at position %d\n", current->data);

        if (current->data == 0)
        {
            ++password;
        }

        current_string += strlen(current_string) + 1;
    }

    printf("The password is: %d\n", password);
}
