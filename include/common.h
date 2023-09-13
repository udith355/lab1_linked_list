#ifndef LAB1_LINKED_LIST_COMMON_H
#define LAB1_LINKED_LIST_COMMON_H

#include "node.h"

struct node *initialize_linked_list(struct node *linkedList, int n);

int Member(long value, struct node *head_p);

int Insert(long value, struct node **head_p);

int Delete(long value, struct node **head_p);

#endif //LAB1_LINKED_LIST_COMMON_H
