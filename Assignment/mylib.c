/**
 * Contains the memory allocation functions, and functions to read the file.
 * 
 *
 * @author Kezia Somerville-Petch.
 * @author Yashna Shetty.
 * @author Hayley Sleeman.
 */

#include <stdio.h> 
#include <stdlib.h> 
#include "mylib.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Allocates memory and prints out to stderr if the memory
 * allocation has failed.
 *
 * @param s - the size of the memory to be allocated.
 *
 * @return result - returns a pointer to where the memory has been allocated.
 */

void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Reallocates memory and prints out an error message if an error is detected.
 *
 * @param p - pointer to the memory that has already been allocated.
 * @param s - the size of memory required for allocation.
 *
 * @return result - returns a pointer to where the memory has been allocated. 
 */

void *erealloc(void *p, size_t s){
    void *result = realloc(p, s);
    if (NULL == result){
        fprintf(stderr, "Memory reallocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Gets a word from a file for the reading of the document and
 * dictionary files.
 *
 * @param s - a pointer to the word being read.
 * @param limit - the number of letters (size of word).
 * @param stream - the file which the word is read from.
 *
 * @return returns the int equivalent of the word.
 */

int getword(char* s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);

    while (!isalnum(c = getc(stream)) && EOF != c);
    if (EOF == c){
        return EOF;
    } else if(--limit > 0){
        *w++ = tolower(c);
    }
    while (--limit > 0){
        if (isalnum(c = getc(stream))){
            *w++ = tolower(c);
        } else if ('\'' == c){
            limit++;
        } else{
            break;
        }
    }
    *w = '\0';
    return w - s;
}

/**
 * Determines whether the number is prime or not.
 *
 * @param x - the number to check if it is prime.
 *
 * @return returns 1 if the number x is prime, returns 0 if the number x isn't
 * prime.
 */

int find_prime(int x){
    int i;
    int prime = 1;
    for (i = 2; i < x; i++){
        if (x % i == 0){
            prime = 0;
        }
    }
    return prime;
}

/**
 * Opens the file for reading and if the file doesn't exist
 * the program exits.
 *
 * @param filename - the name of the file to be opened.
 *
 * @return returns the opened file.
 */

FILE *open_file(char *filename){
    FILE *infile = NULL;
    if (NULL == (infile = fopen(filename, "r"))){
        fprintf(stderr, "%s File Not Found, Try again\n", filename);
        exit(EXIT_FAILURE);
    }
    return infile;
}

/**
 * Prints out the help message telling users how to use the program.
 *
 * @param ifHelp - to signal when to print the help message.
 *
 */

void print_help(int ifHelp){
    if (ifHelp == 1){
        printf("Program Help: \n");
        printf("-c Command: Checks the spelling of words in the input file,\n");
        printf(" printing all unknown words and recorded timing information.\n");
        printf("-d Command: Uses double hashing as the collision resolution\n");
        printf(" strategy. The default strategy is linear probing.\n");
        printf("-e Command: Display the entire contents of the hash table.\n");
        printf("-p Command: Prints the stats information of the hash table.\n");
        printf("-s Command: Display the given number of 'stats'snapshots\n");
        printf("Can only be used in association with -p command\n");
        printf("-t Command: Allows you to assign the hash table size, using \n");
        printf(" the first prime greater or equal to the input integer.\n");
        printf("-h Command: Reprint this help message.\n");

        exit(EXIT_SUCCESS);
    }
}

