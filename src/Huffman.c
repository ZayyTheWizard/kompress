#include "../header/Huffman.h"

// Function to create a new node
Node *newNode(char letter, int frequency)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->letter = letter;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to build the Huffman tree
Node *buildHuffmanTree(char letters[], int frequencies[], int size)
{
    // Create nodes for each letter-frequency pair
    Node *nodes[size];
    for (int i = 0; i < size; i++)
    {
        nodes[i] = newNode(letters[i], frequencies[i]);
    }

    // Build Huffman tree
    while (size > 1)
    {
        // Find the two nodes with the lowest frequencies
        int minIndex1 = 0, minIndex2 = 1;
        if (nodes[minIndex1]->frequency > nodes[minIndex2]->frequency)
        {
            int temp = minIndex1;
            minIndex1 = minIndex2;
            minIndex2 = temp;
        }
        for (int i = 2; i < size; i++)
        {
            if (nodes[i]->frequency < nodes[minIndex1]->frequency)
            {
                minIndex2 = minIndex1;
                minIndex1 = i;
            }
            else if (nodes[i]->frequency < nodes[minIndex2]->frequency)
            {
                minIndex2 = i;
            }
        }

        // Create a new internal node by merging the two nodes with lowest frequencies
        Node *aNode = newNode('$', nodes[minIndex1]->frequency + nodes[minIndex2]->frequency);
        aNode->left = nodes[minIndex1];
        aNode->right = nodes[minIndex2];

        // Remove the two nodes with lowest frequencies from the array and add the new node
        nodes[minIndex1] = aNode;
        nodes[minIndex2] = nodes[size - 1];
        size--;
    }

    // The root node of the Huffman tree is the only node left in the array
    return nodes[0];
}

// Function to print Huffman codes from the Huffman tree
void printCodes(Node *root, int arr[], int top)
{
    // Assign 0 to the left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to the right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, it contains one of the input characters, print the character and its code
    if (!(root->left) && !(root->right))
    {
        printf("%c: ", root->letter);
        for (int i = 0; i < top; ++i)
        {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// Function to print Huffman codes for all characters
void printHuffmanCodes(char letters[], int frequencies[], int size)
{
    // Build the Huffman tree
    Node *root = buildHuffmanTree(letters, frequencies, size);

    // Assign codes to each character using the Huffman tree
    int arr[size], top = 0;
    printCodes(root, arr, top);

    free(root); // Free dynamically allocated memory
}

// Function to generate Huffman codes recursively
void generateCodes(Node *root, char *code, char **codes)
{
    if (root->left)
    {
        char *leftCode = (char *)malloc((strlen(code) + 2) * sizeof(char)); // +2 for '0' and null terminator
        strcpy(leftCode, code);
        strcat(leftCode, "0");
        generateCodes(root->left, leftCode, codes);
        free(leftCode);
    }
    if (root->right)
    {
        char *rightCode = (char *)malloc((strlen(code) + 2) * sizeof(char)); // +2 for '1' and null terminator
        strcpy(rightCode, code);
        strcat(rightCode, "1");
        generateCodes(root->right, rightCode, codes);
        free(rightCode);
    }
    if (!(root->left) && !(root->right))
    {
        // Leaf node, store the code for the character
        codes[root->letter] = strdup(code);
    }
}

// Function to encode a string using Huffman codes
char *searchEquiv(Node *root, char c, char *ans)
{
    if (root == NULL)
    {
        return NULL;
    }

    // If the current node contains the character c
    if (root->letter == c)
    {
        return ans;
    }

    // Traverse left if possible
    if (root->left != NULL)
    {
        strcat(ans, "0"); // Append '0' to the encoding
        char *leftResult = searchEquiv(root->left, c, ans);
        if (leftResult != NULL)
        {
            return leftResult;
        }
        ans[strlen(ans) - 1] = '\0'; // Backtrack if the search in the left subtree was unsuccessful
    }

    // Traverse right if possible
    if (root->right != NULL)
    {
        strcat(ans, "1"); // Append '1' to the encoding
        char *rightResult = searchEquiv(root->right, c, ans);
        if (rightResult != NULL)
        {
            return rightResult;
        }
        ans[strlen(ans) - 1] = '\0'; // Backtrack if the search in the right subtree was unsuccessful
    }

    return NULL; // If character not found in the subtree
}

// Function to encode a string using Huffman coding
char *encodeString(Node *root, char *input)
{
    int len = strlen(input);
    char *encodedString = (char *)malloc(len * 256 * sizeof(char)); // Maximum length of encoded string

    if (encodedString == NULL)
    {
        return NULL;
    }
    encodedString[0] = '\0';

    for (int i = 0; i < len; i += 1)
    {
        // Append the code for each character to the encoded string
        char *ans[256];
        ans[0] = '\0';
        char *equiv = searchEquiv(root, input[i], ans);
        if (equiv == NULL)
        {
            free(encodedString);
            return NULL;
        }
        strcat(encodedString, equiv);
    }

    return encodedString;
}

// Function to generate Huffman codes for all characters
char **generateHuffmanCodes(Node *root)
{
    char **codes = (char **)malloc(512 * sizeof(char *)); // Assuming ASCII characters
    char *code = (char *)malloc(512 * sizeof(char));      // Temporary buffer to store codes
    memset(code, '\0', 512 * sizeof(char));

    generateCodes(root, code, codes);

    free(code);
    return codes;
}

// Function to free memory allocated for Huffman codes
void freeHuffmanCodes(char **codes)
{
    for (int i = 0; i < 512; ++i)
    {
        if (codes[i])
            free(codes[i]);
    }
    free(codes);
}

Node *freeTree(Node *root)
{
    if (!root)
    {
        return NULL;
    }

    root->left = freeTree(root->left);

    root->right = freeTree(root->right);

    free(root);

    return NULL;
}