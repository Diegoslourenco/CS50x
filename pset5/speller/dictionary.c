// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table // Linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH + 1) * 'z'; // ASCI number of alphabetical letter

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    struct node *current = table[hash(word)];

    while (current != NULL)
    {
        if (strcasecmp(word, current->word) == 0)
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }

    return false;
}

// Hashes word to a number djb2 Dan Bernstein http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = 0;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    int hashIndex;

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        n->next = NULL;

        hashIndex = hash(buffer);

        if (table[hashIndex] == NULL)
        {
            table[hashIndex] = n;
        }
        else
        {
            n->next = table[hashIndex];
            table[hashIndex] = n;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = 0;
    struct node *current = NULL;

    for (int i = 0; i < N; i++)
    {
        current = table[i];
        while (current != NULL)
        {
            size++;
            current = current->next;
        }
    }

    if (size == 0)
    {
        return 0;
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    struct node *temp = NULL;
    struct node *current = NULL;

    for (int i = 0; i < N; i++)
    {
        current = table[i];
        while (current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp);
        }
    }

    return true;
}
