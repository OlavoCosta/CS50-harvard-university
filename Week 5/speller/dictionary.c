// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node{
    char word[LENGTH + 1];
    struct node *next;
}node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word){
    // TODO
    //returns true or false.
    int index = hash(word);

    //points to the head of the hash table
    node *cursor = table[index];

    //for loop to navigate until the end node is reached.
    for(node *temp = cursor; temp != NULL; temp = temp->next){
        if(strcasecmp(temp->word, word) == 0) // The strcasecmp() function shall compare, while ignoring differences in case.
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word){
    // TODO: Improve this hash function
    //Get the length of the string and sum the value of the characters.
    unsigned int hashvalue = 0;

    for(int i = 0; i < strlen(word); i++){
        hashvalue += tolower(word[i]);
        hashvalue = (hashvalue * tolower(word[i])) % N;
    }

    return hashvalue;
}

int counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary){
    // TODO
    // will go to the file and read the contents of the dictionary.
    FILE *file = fopen(dictionary, "r");
    if(file == NULL){
        fprintf(stderr, "There has been an error");
        return false;
    }

    char wordlist[LENGTH + 1];

    // will print the words in the word character array
    while(fscanf(file, "%s", wordlist) != EOF){ 
        counter++;

        //for each new loop, allocate memory.
        node *newNode = malloc(sizeof(node));

        if(newNode == NULL){
            return 1;
        }

        //initialize the new node by copying the word to the next node.
        strcpy(newNode->word, wordlist);
        newNode->next = NULL;

        int index = hash(wordlist);

        //put the newest node in the header of that index if the index is not already assigned.
        if(table[index] == NULL){
            table[index] = newNode;
        }
        //point the existing parent node to the index table if the index is assigned, and then make the new node the parent.
        else{
            newNode->next = table[index];

            table[index] = newNode; // head points to the new node.
        }
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void){
    // TODO
    // control over how many nodes have been added.
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void){
    // TODO
    node *tmp = NULL;
    node *cursor = NULL;

    //This cursor will scroll through the lists, turning each one en NULL, freeing up memory space.
    for(int i = 0; i < N; i++){
        cursor = table[i];

        while(cursor != NULL){
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    
    return true;
}
