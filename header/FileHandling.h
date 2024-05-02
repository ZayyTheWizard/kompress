#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Huffman.h"

char *FileToStringInit(char *FileName);
void JSONformatter(char *FileName, char *encoded, Node *root);
void traverseTree(Node *root, FILE *fp);
void OutputEncodedFile(char *FileName, char *encodedString);
char *JSONmessage(char *FileName);
void OutputDecodedFile(char *FileName, char *message);
#endif