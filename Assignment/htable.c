/**
 * Implementing a hash table data structure, through either linear probing or
 * double hashing composition.
 *
 * @author Kezia Somerville-Petch.
 * @author Yashna Shetty.
 * @author Hayley Sleeman.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

#define TABLE_SIZE 113;
#define IF_DOUBLE(x) (DOUBLE_H == (x)->method)

/**
 * The struct for our hashtable, the blueprint for creating an instance
 * of the hashtable.
 */

struct htablerec{
    int *freqs;
    char **keys;
    int num_keys;
    int capacity;
    int *stats;
    hashing_t method;
};

/**
 * Converts the word (string) into it's integer equivalent.
 *
 * @param word - the string we need to convert.
 * @return result - the integer equivalent of the word (string).
 */

static unsigned int htable_word_to_int(char* word){
    unsigned int result = 0;

    while (*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * Calculates the step size based on the collision resolution method (either
 * Linear Probing or Double Hashing) for the hashtable.
 *
 * @param h - the hashtable.
 * @param i_key - the value used in the calculation (in integer form of
 * the string).
 *
 * @return returns 1 if Linear Probing is used or if the capacity of the
 * hashtable is 1, otherwise returns a step size based on the capacity of the
 * table and the i_key.
 */

static unsigned int htable_step(htable h, unsigned int i_key) {
    if(!IF_DOUBLE(h) || h->capacity == 1){
        return 1;
    }else{
        return 1 + (i_key % (h->capacity - 1));
    }
}

/**
 * Frees the memory that is associated with the htable struct.
 *
 * @param h - the hashtable that needs to be freed.
 *
 */

void htable_free(htable h){
    int i;
    for (i = 0; i < h->capacity; i++){
        if (h->keys[i] != NULL){
            free(h->keys[i]);
        }
    }
    free(h->stats);
    free(h->keys);
    free(h->freqs);
    free(h);
}

/**
 * Inserts a word (string) into the hashtable using either Linear Probing or
 * Double Hashing as a collision resolution strategy. This depends on what
 * is specified for the given hashtable. 
 *
 * @param h - the hashtable.
 * @param str - the word (string) that needs to be inserted.
 *
 * @return returns 0 if the word fails to be inserted, returns
 * 1 if the word is inserted into an empty space, returns the frequency
 * of the word if it has already been inserted into the table.
 */

int htable_insert(htable h, char *str){
    int colCount = 0;
    unsigned int to_add = htable_word_to_int(str);
    unsigned int step = htable_step(h, to_add);
    unsigned int index = to_add % h->capacity;   

    if(!IF_DOUBLE(h)){ 
        while (colCount < h->capacity){
            if (h->keys[index] == NULL){ 
                h->keys[index] = emalloc((strlen(str) + 1) * sizeof
                                         h->keys[index][0]);
                strcpy(h->keys[index], str);
                h->freqs[index]++;
                h->num_keys++;
                h->stats[h->num_keys] = colCount;
                return 1;
            } else if(strcmp(h->keys[index], str) == 0){ 
                h->freqs[index]++;
                return h->freqs[index];
            }else{ 
                index = (index + step) % h->capacity;
                colCount++;
            }
            
        }
        return 0;
    }else{
        while(colCount < h->capacity){
            index = (index + colCount * (1 + index %
                                         (h->capacity - 1)))%h->capacity;
            index = index % h->capacity;
            if (h->keys[index] == NULL){
                h->keys[index] = emalloc((strlen(str) + 1) *
                                         sizeof h->keys[index][0]);
                strcpy(h->keys[index], str);
                h->freqs[index]++;
                h->num_keys++; 
                return 1;
            }
            else if(strcmp(h->keys[index], str) == 0){
                return h->freqs[index]++;
            }else{
                return colCount++;
            }
        }
    }
    return 0;
}

/**
 * Creates a new empty hashtable, also allocates memory.
 *
 * @param capacity - the maximum capacity of the table.
 * @param hasht - the collision resolution method to be used (either
 * Linear Probing or Double Hashing).
 *
 * @return h - returns the hashtable.
 */

htable htable_new(int capacity, hashing_t hasht){
    int i;
    htable h = emalloc(sizeof *h);
    h->capacity = capacity;
    h->num_keys = 0;
    h->stats = emalloc(h->capacity * sizeof h->stats[0]);
    h->freqs = emalloc(h->capacity * sizeof h->freqs[0]);
    h->keys = emalloc(h->capacity * sizeof h->keys[0]);
    h->method = hasht;
    for (i = 0; i < h->capacity; i++){
        h->freqs[i] = 0;
        h->keys[i] = NULL;
        h->stats[i] = 0;
    }
    return h;
}

/**
 * Prints all the freqencies and keys of the hashtable.
 *
 * @param h - the hashtable to be printed out.
 * @param f - a function passed as an argument allowing the use
 * of print_info in asgn.c.
 *
 */

void htable_print(htable h, void f(int freq, char *key)){
    int i;
    for (i = 0; i < h->capacity; i++){
        if(h->freqs[i] > 0){
            f(h->freqs[i], h->keys[i]);
        }
    }
}

/**
 * Searches for a key in the hashtable.
 *
 * @param h - the hashtable to be searched.
 * @param str - the key we are searching for.
 *
 * @return returns 0 if the key cannot be found, otherwise returns
 * the frequency of the key if it can be found in the hashtable.
 */

int htable_search(htable h, char *str){
    int colls = 0;
    unsigned int wordValue = htable_word_to_int(str);
    unsigned int step = htable_step(h, wordValue);
    unsigned int index = wordValue % h->capacity;

    if(!IF_DOUBLE(h)){ 
        while (h->keys[index] != NULL && strcmp(h->keys[index], str)
               != 0 && colls < h->capacity){
            colls++;
            index = (index + step) % h->capacity;
        }
        if (colls == h->capacity){
            return 0;
        } else{
            return h->freqs[index];
        }
    }else{
        while(colls < h->capacity){
            index = (index + colls * (1 + index %
                                      (h->capacity - 1)))%h->capacity;
            index = index % h->capacity;
            if(h->keys[index] != NULL && strcmp(h->keys[index], str) == 0){
                return 1;
            }else{
                colls++;
                index++;
            }
        }
        return 0;
    }
    return 0;            
}

/**
 * Prints out the entire hashtable including the position, frequency, stats and
 * word.
 *
 * @li Pos - The position in the table.
 * @li Freq - The frequency of the word in the table.
 * @li Stats - The collision count that has occurred at that position.
 * @li Word - The word (key) stored at that position. 
 *
 * @param h - the hashtable to be printed.
 * @param stream - the stream we are printing the table to. 
 * 
 */

void htable_print_entire_table(htable h, FILE *stream){
    int i;
    fprintf(stream, "%5s %5s %5s   %s\n", "Pos", "Freq", "Stats", "Word");
    fprintf(stream, "----------------------------------------\n");
    for (i = 0; i < h->capacity; i++){
        if(h->keys[i] != NULL){
            fprintf(stream, "%5d %5d %5d   %s\n", i, h->freqs[i],
                    h->stats[i], h->keys[i]);
        } else{
            fprintf(stream, "%5d %5d %5d   \n", i, h->freqs[i], h->stats[i]); 
        }
    }
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;

            } 
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];

            }
            average_collisions += h->stats[i];
        }
    
        fprintf(stream, "%4d %10d %11.1f %10.2f %11d\n", percent_full, 
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n", 
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
    fprintf(stream, "Percent   Current    Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries    At Home   Collisions   Collisions\n");
    fprintf(stream, "------------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "------------------------------------------------------\n\n");
}

