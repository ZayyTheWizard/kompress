# C and Bash Compression Tool

# Huffman Coding #Huffman

Huffman coding is a lossless data compression algorithm. The idea is to assign variable-length codes to input characters, lengths of the assigned codes are based on the frequencies of corresponding characters.

#### Algorithm For encoding 

1. Calculate the frequency of each character in the string
2. Sort the characters in increasing order of the frequency. These are stored in a priority queue
3. Make each unique character as a leaf node.
4. Create an empty node z. Assign the minimum frequency to the left child of z and assign the second minimum frequency to the right child of z. Set the value of the z as the sum of the above two minimum frequencies.
5. Remove these two minimum frequencies from Q and add the sum into the list of frequencies (* denote the internal nodes in the figure above).
6. Insert node z into the tree.
7. Repeat steps 3 to 5 for all the characters.
8. For each non-leaf node, assign 0 to the left edge and 1 to the right edge.

#### Algorithm for Decoding

For decoding the code, we can take the code and traverse through the tree to find the character.

# General Project Idea 

Have a bash script that searches a specific directory, that given a text file( or any other file type) encodes it using the **Huffman Coding Algorithm**, with the help of a C program. And stores the encoded file else where.

## Day 1

#### Setting Up
	setting up inlcuded making sure I can read out put and starting the outlining for the file proccessing 

## Day 2

#### Added Bash script

Added a bash script to automatically compile and run my c program so that I do not have to constantly type it out every time.

```sh
#!/bin/bash

gcc -o app src/Main.c src/FileHandling.c

./app test.txt
```

#### Finished File Handling Functions

Finish file handling Function FileToStringInit.
```c
char *FileToStringInit(char *FileName)
{
// Pre-Proccessing step Turns file in to a string to be sent for encoding

FILE *fptr;

  

char Dir[256] = "/Notes";

  

strcat(Dir, FileName);

  

if ((fptr = fopen(Dir, "rt")) == NULL)
{

printf("Couldn't locate file: %s\n", FileName);

return NULL;

}

  

assert(fptr);

fseek(fptr, 0, SEEK_END);

length = ftell(fptr);

fseek(fptr, 0, SEEK_SET);

FileContent = (char *)malloc(length + 1);

FileContent[length] = '\0';

fread(FileContent, 1, length, fptr);

fclose(fptr);

  

printf("File Content as string: %s", FileContent);

return FileContent;
}
```

#### Added Vector struct
Added Vector ops 

#### Deleted Vector Ops 
because there only so many characters realistically

## Day 4

#### Added Set Struct and Accents

```c
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

#endif

