#define CLIST_IMPLEMENTATION
#include "../header/FileHandling.h"
#include "../header/CList.h"
#include "../header/Huffman.h"
#include <ctype.h>
#define UNUSED(x) (void)(x)

int AddToList(const char *str, list **List);
void removeWhitespace(char *str);

int main(int _, char *argv[])
{
    UNUSED(_);
    if (argv[1] == NULL)
    {
        printf("No file provided!\n");
        return 1;
    }

    if (argv[2] == NULL)
    {
        printf("Encode or decode?\n");
        return 1;
    }

    char *FileAsStr;
    if ((FileAsStr = FileToStringInit(argv[1])) == NULL)
    {
        printf("Couldn't Locate file: %s\n", argv[1]);
        return 1;
    }

    if (strcmp(argv[2], "encode") == 0)
    {
        removeWhitespace(FileAsStr);
        list *ListPtr = NULL;

        int count = AddToList(FileAsStr, &ListPtr);
        bubbleSort(&ListPtr, count);

        char Letters[count];
        int Frequency[count];

        list *curr = ListPtr;

        for (int i = 0; i < count && curr != NULL; i += 1)
        {
            Letters[i] = curr->Letter;
            Frequency[i] = curr->Frequency;
            curr = curr->next;
        }
        freeList(ListPtr);

        Node *root = buildHuffmanTree(Letters, Frequency, count);

        char *encodedString = encodeString(root, FileAsStr);
        JSONformatter(argv[1], encodedString, root);

        freeTree(root);
        free(encodedString);
        printf("Succesfly Encoded File\n");
    }
    else if (strcmp(argv[2], "decode") == 0)
    {
        char *message = JSONmessage(argv[1]);
        if (message == NULL)
        {
            // Handle error
            printf("Error decoding file\n");
            return -1;
        }
        else
        {
            // Print the result
            OutputDecodedFile(argv[1], message);
            printf("Successfully Decoded File\n");

            free(message);
        }
    }

    free(FileAsStr);
    return 0;
}

int AddToList(const char *str, list **List)
{
    int CurrCount = 0;
    // Iterate through each character until the null terminator is reached
    for (int i = 0; str[i] != '\0'; i++)
    {
        // Print the current character
        if (search(*List, str[i]))
        {
            Update(&(*List), str[i]);
        }
        else
        {
            Insert(&(*List), str[i], 1);
            CurrCount++;
        }
    }

    return CurrCount;
}

void removeWhitespace(char *str)
{
    int i, j;
    for (i = 0; i <= strlen(str); i++)
    {
        if (isspace((unsigned char)str[i]))
        {
            str[i] = '_';
        }
    }
    str[i] = '\0'; // Null-terminate the modified string
}