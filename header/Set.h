#include <stdbool.h>
#include <stdlib.h>
#pragma once
#ifndef SET_H
#define SET_H

typedef struct
{
    /* data */
    char *mySet;
    int Free;
} MySet;

void set_init(MySet *thisSet);
bool IsPresent(MySet *thisSet, char key);
int PushS(MySet *thisSet, char key);
int RemoveS(MySet *thisSet, char key);
void printSet(MySet *thisSet);
#endif

#ifdef SET_IMPLEMENTATION
void set_init(MySet *thisSet)
{
    if (thisSet == NULL)
    {
        printf("Error: Null pointer passed to set_init\n");
        return;
    }

    thisSet->mySet = (char *)malloc(52);
    if (thisSet->mySet == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return;
    }
    thisSet->Free = 0;
}
bool IsPresent(MySet *thisSet, char key)
{
    for (int i = 0; i <= thisSet->Free; i += 1)
    {
        if (thisSet->mySet[i] == key)
        {
            return true;
        }
    }

    return false;
}

int PushS(MySet *thisSet, char key)
{
    if (thisSet->Free == 52)
    {
        printf("Set is full");
        return -1;
    }

    thisSet->mySet[thisSet->Free] = key;
    thisSet->Free += 1;
    return 0;
}

int RemoveS(MySet *thisSet, char key)
{
    if (!IsPresent(thisSet, key))
    {
        return -1;
    }

    for (int i = 0; i <= thisSet->Free; i += 1)
    {
        if (thisSet->mySet[i] == key)
        {
            thisSet->mySet[i] = NULL;
        }
    }

    return 0;
}

void printSet(MySet *thisSet)
{
    for (int i = 0; i < thisSet->Free; i += 1)
    {
        printf("%d, %c\n", i + 1, thisSet->mySet[i]);
    }
}

void FreeSet(MySet *thisSet)
{
    free(thisSet->mySet);
    thisSet->Free = 0;
}
#endif
