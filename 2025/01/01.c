#include <stdio.h>
#include <stdlib.h>

// char *combinations[] =
// {
//     "L68",
//     "L30",
//     "R48",
//     "L5",
//     "R60",
//     "L55",
//     "L1",
//     "L99",
//     "R14",
//     "L82"
// };

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;

typedef struct Input
{
    FILE *file;
    char *buffer;
    long number_of_bytes;
} Input;

void insert_at_end(int value);

void make_list_circular(void);

struct Input *read_input(void);

void process_combinations(const char *combinations);

struct Node *create_node(int value);

void print_list(void);

void null_terminate_strings(char *buffer);

int main(void)
{
    for(int i = 0; i < 100; ++i)
    {
        insert_at_end(i);
    }

    make_list_circular();

    print_list();

    Input* input = read_input();

    null_terminate_strings(input->buffer);

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
    input->number_of_bytes = ftell(input->file) + 1; // so we can null terminate it
    fseek(input->file, 0L, SEEK_SET);

    input->buffer = calloc(input->number_of_bytes, sizeof(char));

    if (input->buffer == NULL)
    {
        printf("Error: Failed to allocate memory for input->buffer.\n");
        exit(EXIT_FAILURE);
    }

    fread(input->buffer, sizeof(char), input->number_of_bytes, input->file);
    fclose(input->file);

    printf("contents of input.txt\n\n%s", input->buffer);

    return input;
}

struct Node *create_node(int value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

void insert_at_end(int value)
{
    Node *new_node = create_node(value);

    if (head == NULL)
    {
        head = new_node;
        tail = new_node;
        return;
    }

    Node *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = new_node;
    new_node->prev = temp;
    tail = new_node;
}

void make_list_circular(void)
{
    if (head != NULL && tail != NULL)
    {
        tail->next = head;
        head->prev = tail;
    }
}

void print_list(void)
{
    Node *current = head;

    do
    {
        printf("%d\n", current->data);
        current = current->next;
    } while (current != head);
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
void process_combinations(const char *combinations)
{
    Node *current = head;
    current = set_dial_to_starting_position(current, 50);
    printf("Dial has been turned to %d\n", current->data);

    int password = 0;

    for (int i = 0; i < number_of_combinations; ++i)
    {
        char direction = *(combinations[i]);
        char *digits = combinations[i] + 1;
        int turn_amount = convert_string_to_int(digits);

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
    }

    printf("The password is: %d\n", password);
}
