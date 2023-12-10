// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 45;

// Hash table
node *table[N];

unsigned int hash(const char *word)
{
    unsigned int index = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        index += tolower(word[i]) - 'a';
    }
    return index % N;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dic file.
    FILE *file = fopen(dictionary, "r");
    // check if the dic not open.
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer to read words into dic
    char phrase[LENGTH + 1];

    // Read strings from file one at a time.
    while (fscanf(file, "%s", phrase) != EOF)
    {
        // new node that is going to be store that particular word.
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }
        // Copy word into node.
        strcpy(n->word, phrase);
        n->next = NULL;
        // Insert this n into a hash table.
        int buket = hash(phrase);
        if (table[buket] == NULL)
        {
            table[buket] = n;
        }
        else
        {
            n->next = table[buket];
            table[buket] = n;
        }
    }
    // Close the open file and return true.
    fclose(file);
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert word to lowercase
    char lword[LENGTH + 1];
    for (int i = 0; i <= strlen(word); i++)
    {
        lword[i] = tolower(word[i]);
    }

    // Calculate hash value
    unsigned int h = hash(lword);

    // Traverse the linked list at the hash index
    node *cursor = table[h];

    while (cursor != NULL)
    {
        // Compare lowercase word with dictionary word
        if (strcasecmp(cursor->word, lword) == 0)
        {
            // Word found in dictionary
            return true;
        }
        // Move to the next pointer.
        cursor = cursor->next;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int sum = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            sum += 1;
            cursor = cursor->next;
        }
    }
    return sum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
