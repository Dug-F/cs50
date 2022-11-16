// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

// function prototypes
bool initialise_table();
bool load_word(char *word);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    int compare;

    for (node *n = table[hash_value]->next; n != NULL; n = n->next)
    {
        if (strlen(n->word) != strlen(word))
        {
            continue;
        }

        compare = strcasecmp(word, n->word);

        if (compare == 0)
        {
            return true;
        }

        if (compare > 0)
        {
            return false;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int length = strlen(word);
    unsigned hash1 = (length > 0) ? (toupper(word[0]) - 'A') * 26 * 26 : 0;
    hash1 = (hash1 > 25 * 26 * 26) ? 25 * 26 * 26 : hash1;
    unsigned hash2 = (length > 1) ? (toupper(word[1]) - 'A') * 26 : 0;
    hash2 = (hash2 > 25 * 26) ? 25 * 26 : hash2;
    unsigned hash3 = (length > 2) ? (toupper(word[2]) - 'A')  : 0;
    hash3 = (hash3 > 25) ? 25 : hash3;

    return hash1 + hash2 + hash3;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    char word[LENGTH + 1];
    int index = 0;

    if (!initialise_table())
    {
        return false;
    }

    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // read through dictionary file
    int buffer_chars = fread(&buffer, sizeof(char), BUFFER_SIZE, file);
    while (buffer_chars != 0)
    {
        for (int i = 0; i < buffer_chars; i++)
        {
            if (buffer[i] == '\n')
            {
                // load word into table
                word[index] = '\0';
                if (!load_word(word))
                {
                    return false;
                }
                index = 0;
            }
            else
            {
                word[index] = buffer[i];
                index ++;
            }
        }

        buffer_chars = fread(&buffer, sizeof(char), BUFFER_SIZE, file);
    }
    fclose(file);

    for (int i = 0; i < N; i++)
    {
        if (table[i]->next != NULL)
        {
            node *tmp = table[i]->next;
            while (tmp != NULL)
            {
                printf("word: %s\n",tmp->word);
                tmp = tmp->next;
            }
        }
    }

    return true;
}

bool load_word(char *word)
{
    // load new word into table.  Returns true if load successful, otherwise false

    // create new node;
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return false;
    }

    // load word into node
    for (int i = 0, length = strlen(word) + 1; i < length; i++)
    {
        n->word[i] = word[i];
    }

    unsigned hash_value = hash(word);
    n->next = table[hash_value]->next;
    table[hash_value]->next = n;

    return true;
}

bool initialise_table()
{
    // initialise table.  Returns true if successfully initialised, otherwise false.
    for (int i = 0; i < N; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        table[i] = n;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]->next; tmp != NULL; tmp = tmp->next)
        {
            count++;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // free all table nodes
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *tmp = n->next;
            free(n);
            n = tmp;
        }
    }

    return true;
}
