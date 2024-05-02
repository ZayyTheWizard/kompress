#include "../header/FileHandling.h"

// File Proccessing
char *FileContent;
long length;

char *FileToStringInit(char *FileName)
{
    FILE *fptr = fopen(FileName, "rb");
    if (fptr == NULL)
    {
        printf("Couldn't locate file: %s\n", FileName);
        return NULL;
    }

    // Determine the length of the file
    fseek(fptr, 0, SEEK_END);
    long length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    // Allocate memory for file content
    char *FileContent = (char *)malloc(length + 1); // +1 for null terminator
    if (FileContent == NULL)
    {
        perror("Error allocating memory for file content");
        fclose(fptr);
        return NULL;
    }

    // Read the file content into the allocated memory
    size_t bytes_read = fread(FileContent, 1, length, fptr);
    if (bytes_read != length)
    {
        perror("Error reading file");
        fclose(fptr);
        free(FileContent); // Free allocated memory
        return NULL;
    }

    // Null-terminate the string
    FileContent[length] = '\0';

    fclose(fptr);

    return FileContent;
}

void traverseTree(Node *root, FILE *fp)
{
    if (root)
    {
        fprintf(fp, "{\\\"char\\\": \\\"%c\\\", \\\"freq\\\": \\\"%u\\\"", root->letter, root->frequency);
        if (root->left || root->right)
        {
            fprintf(fp, ", \\\"left\\\": ");
            traverseTree(root->left, fp);
            fprintf(fp, ", \\\"right\\\": ");
            traverseTree(root->right, fp);
        }
        fprintf(fp, "}");
    }
}

// OutPuts code in json format
void JSONformatter(char *FileName, char *encoded, Node *root)
{
    FILE *fp = fopen(FileName, "wb");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "{\\\"message\\\": \\\"%s\\\",\\\"type\\\": \\\"huffman tree\\\",\\\"root\\\": ", encoded);
    traverseTree(root, fp);
    fprintf(fp, "}");

    fclose(fp);
}

// Returns the encoded message
char *JSONmessage(char *FileName)
{
    char *json = FileToStringInit(FileName);

    // Calculate the length of the command string
    int command_length = strlen("python3 parser.py \"") + strlen(json) + strlen("\"") + 1; // +1 for null terminator

    // Dynamically allocate memory for command
    char *command = malloc(command_length);
    if (command == NULL)
    {
        perror("Error allocating memory for command");
        return NULL;
    }

    // Construct the command string
    sprintf(command, "python3 parser_1.py \"%s\"", json);

    FILE *fp = popen(command, "r");
    free(command); // Free dynamically allocated memory after use

    if (fp == NULL)
    {
        perror("Error executing command");
        return NULL;
    }

    // Initialize result pointer and size
    char *result = NULL;
    size_t result_size = 0;

    // Read the result from the Python script
    ssize_t bytes_read;
    size_t total_bytes_read = 0;
    const size_t chunk_size = 100; // Initial chunk size

    do
    {
        // Resize result buffer if needed
        result_size += chunk_size;
        result = realloc(result, result_size);
        if (result == NULL)
        {
            perror("Error reallocating memory for result");
            pclose(fp);
            return NULL;
        }

        // Read a chunk from the Python script
        bytes_read = fread(result + total_bytes_read, 1, chunk_size, fp);
        if (bytes_read < 0)
        {
            perror("Error reading result");
            free(result); // Free dynamically allocated memory in case of error reading result
            pclose(fp);
            return NULL;
        }

        total_bytes_read += bytes_read;
    } while (bytes_read == chunk_size);

    // Close the file stream
    pclose(fp);

    // Null-terminate the result string
    result[total_bytes_read] = '\0';

    return result;
}

// Output File as encoded.
void OutputEncodedFile(char *FileName, char *encodedString)
{
    FILE *fptr = fopen(FileName, "wb");
    if (fptr)
    {
        fwrite(encodedString, sizeof(char), strlen(encodedString), fptr);
        fclose(fptr);
        printf("Encoded string has been written to %s file.\n", FileName);
    }
    else
    {
        printf("Error: Unable to open file for writing.\n");
    }
}

void OutputDecodedFile(char *FileName, char *message)
{
    // Return Decoded file
    FILE *fptr = fopen(FileName, "wb");
    if (fptr)
    {
        fwrite(message, sizeof(char), strlen(message), fptr);
        fclose(fptr);
    }
    else
    {
        printf("Error: Unable to open file for writing.\n");
    }
}
