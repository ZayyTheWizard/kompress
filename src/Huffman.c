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

// Function to create a new priority queue node
PriorityQueueNode *newPriorityQueueNode(Node *node)
{
    PriorityQueueNode *pqNode = (PriorityQueueNode *)malloc(sizeof(PriorityQueueNode));
    pqNode->node = node;
    pqNode->next = NULL;
    return pqNode;
}

// Function to insert a new node into the priority queue
void insert(PriorityQueueNode **head, Node *node)
{
    PriorityQueueNode *start = (*head);

    // Create a new priority queue node
    PriorityQueueNode *temp = newPriorityQueueNode(node);

    // Special case: The priority of the new node is less than the head
    if ((*head) == NULL || (*head)->node->frequency >= node->frequency)
    {
        temp->next = *head;
        (*head) = temp;
    }
    else
    {
        // Locate the node before the point of insertion
        while (start->next != NULL && start->next->node->frequency < node->frequency)
        {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

// Function to remove the top node of the priority queue
Node *removeMin(PriorityQueueNode **head)
{
    Node *popped = (*head)->node;
    (*head) = (*head)->next;
    return popped;
}

// Function to build the Huffman tree
Node *buildHuffmanTree(char letters[], int frequencies[], int size)
{
    PriorityQueueNode *priorityQueue = NULL;

    // Create a leaf node for each character and add it to the priority queue
    for (int i = 0; i < size; ++i)
    {
        Node *node = newNode(letters[i], frequencies[i]);
        insert(&priorityQueue, node);
    }

    // Check if the priority queue is empty or has only one node
    while (priorityQueue != NULL && priorityQueue->next != NULL)
    {
        // Remove the two nodes with the lowest frequency from the priority queue
        Node *left = removeMin(&priorityQueue);
        Node *right = removeMin(&priorityQueue);

        // Create a new internal node with the sum of the frequencies
        Node *internalNode = newNode('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        // Insert the new internal node back into the priority queue
        insert(&priorityQueue, internalNode);
    }

    // The remaining node in the priority queue is the root of the Huffman tree
    Node *root = NULL;
    if (priorityQueue != NULL)
    {
        root = removeMin(&priorityQueue);
    }

    return root;
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