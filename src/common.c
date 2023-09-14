#include <stdio.h>
#include <stdlib.h>
#include "../include/node.h"
#include "../include/common.h"

int Member(long value, struct node *head_p) {
    struct node *current_p = head_p;
    while (current_p != NULL && current_p->data < value)
        current_p = current_p->next;
    if (current_p == NULL || current_p->data > value) {
        return 0; /* Not a member */
    } else {
        return 1; /* A member */
    }
}

int Insert(long value, struct node **head_p) {
    struct node *current_p = *head_p;
    struct node *previous_p = NULL;
    struct node *temporary_p;

    while (current_p != NULL && current_p->data < value) {
        previous_p = current_p;
        current_p = current_p->next;
    }
    if (current_p == NULL || current_p->data > value) {
        temporary_p = malloc(sizeof(struct node));
        temporary_p->data = value;
        temporary_p->next = current_p;
        if (previous_p == NULL) /* New first value */
            *head_p = temporary_p;
        else
            previous_p->next = temporary_p;
        return 1;
    } else { /* Value already in the list*/
        return 0;
    }
}

int Delete(long value, struct node **head_p) {
    struct node *current_p = *head_p;
    struct node *previous_p = NULL;

    while (current_p != NULL && current_p->data < value) {
        previous_p = current_p;
        current_p = current_p->next;
    }
    if (current_p != NULL && current_p->data == value) {
        if (previous_p == NULL) {
            *head_p = current_p->next;
            free(current_p);
        } else {
            previous_p->next = current_p->next;
            free(current_p);
        }
        return 1;
    } else {
        return 0;
    }
}

struct node *initialize_linked_list(struct node *linkedList, int n) {
    linkedList = NULL;
    int size = 0;
    while (size < n) {
        long randomNumber = rand() % 65536;
        size += Insert(randomNumber, &linkedList);
    }
    return linkedList;
}



