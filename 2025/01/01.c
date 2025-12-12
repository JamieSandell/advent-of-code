#include <stdio.h>
#include <stdlib.h>

char *combinations[] =
{
    "S50",
    "L68",
    "L30",
    "R48",
    "L5",
    "R60",
    "L55",
    "L1",
    "L99",
    "R14",
    "L82"
};

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;

void insert_at_end(int value);

void make_list_circular(void);

void process_combinations(void);

struct Node *create_node(int value);

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

// assumes at least 2 combinations present, the first is the starting point, the second onwards are the direction to turn and the amount to turn by
void process_combinations(void)
{
    int number_of_combinations = sizeof(combinations) / sizeof(combinations[0]);

    char *starting_point_digits = combinations[0] + 1;
    int starting_point = convert_string_to_int(starting_point_digits);
    printf("Starting point is: %d\n", starting_point);

    Node *current = head;
    current = set_dial_to_starting_position(current, starting_point);
    printf("Dial has been turned to %d\n", current->data);

    int password = 0;

    for (int i = 1; i < number_of_combinations; ++i)
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

int main(void)
{
    for(int i = 0; i < 100; ++i)
    {
        insert_at_end(i);
    }

    make_list_circular();

    print_list();

    process_combinations();

    return EXIT_SUCCESS;
}
