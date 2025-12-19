#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>

typedef struct Node Node;

void insert_at_end(int value);

void make_list_circular(void);

Node *create_node(int value);

void print_list(void);

#endif