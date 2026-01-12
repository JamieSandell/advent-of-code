#include <stdlib.h>
#include "linked_list.h"

struct List *ll_create_list(void)
{
    List *new_list = malloc(sizeof(List));

    if (new_list == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
}

struct List_Node *ll_create_node(int value)
{
    List_Node *new_node = malloc(sizeof(List_Node));

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

void ll_insert_at_end(List *list, int value)
{
    List_Node *new_node = ll_create_node(value);

    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
        return;
    }

    list->tail->next = new_node;
    new_node->prev = list->tail;
    list->tail = new_node;
}

void ll_make_list_circular(List *list)
{
    if (list->head != NULL && list->tail != NULL)
    {
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }
}

void ll_print_list(List *list)
{
    List_Node *current = list->head;

    do
    {
        printf("%d\n", current->data);
        current = current->next;
    } while (current != list->head);
}
