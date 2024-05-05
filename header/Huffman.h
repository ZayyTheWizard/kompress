#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>

typedef struct Node
{
    char letter;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(char letter, int frequency);
Node *buildHuffmanTree(char letters[], int frequencies[], int size);
void printCodes(Node *root, int arr[], int top);
void printHuffmanCodes(char letters[], int frequencies[], int size);
void generateCodes(Node *root, char *code, char **codes);
char *encodeString(Node *root, char *input);
char **generateHuffmanCodes(Node *root);
void freeHuffmanCodes(char **codes);
char *searchEquiv(Node *root, char c, char *ans);
Node *freeTree(Node *root);
#endif