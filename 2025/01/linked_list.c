#include <stdlib.h>
#include "linked_list.h"

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

Node *head = NULL;
Node *tail = NULL;

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

    tail->next = new_node;
    new_node->prev = tail;
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
