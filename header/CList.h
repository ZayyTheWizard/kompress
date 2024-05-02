#include <stdlib.h>
#include <stdbool.h>
#pragma once
#ifndef CLIST_H
#define CLIST_H

typedef struct
{
    char Letter;
    int Frequency;
    struct list *next;
} list;

// Public methods capitol, priv methods lowercase..
bool search(list *head, char letter);
void Insert(list **head, char letter, int num);
void Update(list **head, char letter);
list *swap(list *ptr1, list *ptr2);
void bubbleSort(list **head, int count);
void PrintList(list *head);
#endif

#ifdef CLIST_IMPLEMENTATION
bool search(list *head, char letter) // Linear Search
{
    list *curr = head;

    while (curr != NULL)
    {
        if (curr->Letter == letter)
        {
            return true; // Letter does infact exist
        }
        curr = curr->next;
    }

    return false; // Letter not found
}
void Insert(list **head, char letter, int num)
{
    list *newNode = (list *)malloc(sizeof(list)); // Allocate memory for the new node
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->Letter = letter; // Set the data of the new node
    newNode->Frequency = num;
    newNode->next = NULL; // Make the new node point to NULL, as it will be the last node

    if (*head == NULL)
    { // If the list is empty, make the head point to the new node
        *head = newNode;
        return;
    }

    list *current = *head;
    while (current->next != NULL)
    { // Traverse the list to find the last node
        current = current->next;
    }

    current->next = newNode; // Set the next of the last node to the new node
}

void Update(list **head, char letter)
{
    list *curr = *head;

    while (curr != NULL)
    {
        if (curr->Letter == letter)
        {
            curr->Frequency += 1;
            return;
        }

        curr = curr->next;
    }
    return;
}

list *swap(list *ptr1, list *ptr2)
{
    list *tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

/* Function to sort the list */
void bubbleSort(list **head, int count)
{
    list **h;
    int i, j, swapped;

    for (i = 0; i <= count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            list *p1 = *h;
            list *p2 = p1->next;

            if (p1->Frequency > p2->Frequency)
            {

                /* update the link after swapping */
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        /* break if the loop ended without any swap */
        if (swapped == 0)
        {
            break;
        }
    }
}

void PrintList(list *head)
{
    list *curr = head;

    while (curr != NULL)
    {
        printf("%c: %d -> ", curr->Letter, curr->Frequency);
        curr = curr->next;
    }

    printf("\n");
}
#endif
