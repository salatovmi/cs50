// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 186019;

// Hash table
node *table[N];
unsigned int words_count = 0;

bool add_to_table(const char *word);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char p[strlen(word) + 1];
    strcpy(p, word);
    char *copy = p;
    for ( ; *copy; ++copy) *copy = tolower(*copy);
    int hash_index = hash(p);
    node *tmp = table[hash_index];
    if (tmp == NULL)
    {
        return false;
    }
    while(true)
    {
        if(strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }
        tmp = tmp -> next;
        if(tmp == NULL) break;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Dictionary doesn't exist or couldn't be opened\n");
        return false;
    }
    char *word = malloc(sizeof(char) * (LENGTH + 1));
    while ((fscanf(dict, "%s", word)) != EOF)
    {
        if (!add_to_table(word))
        {
            return false;
        }
        *word = '\0';
        words_count++;
    }
    free(word);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* temp;
    node* first;

    for(int n = 0; n < N; n++)
    {
        if (table[n] != NULL)
        {
            first = table[n];
            while (first != NULL)
            {
                temp = first->next;
                free(first);
                first = temp;
            }
        }
    }
    return true;
}


bool add_to_table(const char *word)
{
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return false;
    }
    new_node -> next = NULL;
    strcpy(new_node -> word, word);

    unsigned int hashIndex = hash(word);

    if(table[hashIndex] == NULL)
    {
        table[hashIndex] = new_node;
    }
    else
    {
        new_node -> next = table[hashIndex];
        table[hashIndex] = new_node;
    }
    return true;
}
