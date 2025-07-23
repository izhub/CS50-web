// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000 ;
unsigned int wordcount = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];
    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // source: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c = 0;
    while ((c = *word++) != '\0')
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }
    if (hash < 0)
    {
        hash = -hash;
    }
    return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("file not found.\n");
        return false;
    }

    char read[LENGTH + 1];
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // read strings from file one at a time
    while (fscanf(file, "%s", read) != EOF)
    {
        // create a new node for each word
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return false;
        }
        strcpy(newnode->word, read);

        // hash word to obtain a hash value
        int h = hash(read);

        // set new pointer
        newnode->next = table[h];

        // set head to new pointer; hash value into hashtable index with new node
        table[h] = newnode;

        // for size();
        wordcount++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
// valgrind ./speller texts/cat.txt
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while ( cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}

/*
leaks check:
valgrind ./speller texts/cat.txt
help50 valgrind ./speller texts/cat.txt

Testing:
./speller texts/lalaland.txt
~cs50/2019/fall/pset5/speller texts/lalaland.txt

compare with staff:
./speller texts/lalaland.txt > student.txt
~cs50/2019/fall/pset5/speller texts/lalaland.txt > staff.txt
diff -y student.txt staff.txt
diff -y student.txt keys/lalaland.txt

check50 cs50/problems/2020/x/speller
submit50 submit50 cs50/problems/2020/x/speller

~cs50/2019/fall/pset5/speller texts/lalaland.txt

big board:
check50 cs50/problems/2020/x/challenges/speller
submit50 cs50/problems/2020/x/challenges/speller
*/