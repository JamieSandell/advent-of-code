#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>

typedef struct List_Node
{
    int data;
    struct List_Node *next;
    struct List_Node *prev;
} List_Node;

typedef struct List
{
    List_Node *head;
    List_Node *tail;
} List;

void ll_insert_at_end(List *list, int value);

void ll_make_list_circular(List *list);

List *ll_create_list(void);

List_Node *ll_create_node(int value);

void ll_print_list(List *list);

#endif