/**
 * Reads in a file and stores it in a hash table using either double hashing
 * or linear probing (default) to resolve collisions. Various commands allow
 * many hash table modifications including; spell checking and printing of
 * unknown words, specifying the collision resolution method used to fill the
 * hash table, displaying the contents or 'stats' of said hash table.
 *
 * Specific commands also allow the user to define the table size, 'snapshot'
 * integer and ask for help/command explanation.
 *
 * @author Kezia Somerville-Petch
 * @author Hayley Sleeman
 * @author Yashna Shetty 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include <getopt.h>
#include <time.h>

/**
 * Displays the word and frequency of the word within the hash table, printing
 * it to stdout.
 *
 * @param freq the number of times the specific word is repeated.
 * @param word the word itself.
 */
static void print_info(int freq, char *word){
    printf("%-4d %s\n", freq, word);
}

/**
 * Main function, including mylib.h and htable.h.
 *
 * Allows the manipulation of the hash table, through the previously
 * explained cases.
 *
 * @param argc variable passed to getopt.
 * @param argv variable passed to getopt allowing file recognition.
 */ 
int main(int argc, char **argv){

    clock_t start_1, end_1, start_2, end_2;
    htable h = NULL;
    double tableFill, tableSearch;
    char option;
    char *fileName;
    char word[256];

    const char *optstring = "c:deps:t:h";
    FILE *file;

    int num = 0;
    int wordsUnknown = 0;
    int numSnaps = 0;

    /** Command line Cases */
    int tableSize = 113;
    int spellcheck = 0;
    int hashType = 0;
    int printTable = 0;
    int printStats = 0;
    int snapshots = 0;
    int ifHelp = 0;
    
    file = NULL;
    fileName = NULL;
    
    tableFill = 0;
    tableSearch = 0;

    while ((option = getopt(argc, argv, optstring)) != EOF){
        switch (option){
            case 'c':
                
                fileName = optarg;
                spellcheck = 1;

                break;
            case 'd':
                
                hashType = 1;
                
                break;
            case 'e':
                
                printTable= 1;
                
                break;
            case 'p':

                printStats = 1;
                
                break;
            case 's':

                snapshots = 1;
                numSnaps = atoi(optarg);
                
                break;
            case 't':
                
                tableSize = atoi(optarg);
                
                if (tableSize == 0){
                    tableSize = 2;
                }
                
                break;
            case 'h':

                ifHelp = 1;
                
                break;
                
            default:

                ifHelp = 1;
                
                break;
        }
    }

    /** Runs print_help, printing the  help message if ifHelp == 1 */
    print_help(ifHelp);

    /** Assigns table size, to the next highest prime number from the input */
    num = tableSize;
    while (find_prime(num) == 0){
        num++;
    }
    tableSize = num;
    
    start_1 = clock();

    /** Determines if the hash table is filled using double h or linear p */
    if(hashType){
        h = htable_new(tableSize, DOUBLE_H);
    }else{
        h = htable_new(tableSize, LINEAR_P);
    }

    /** Inserts words into the created hash table */
    while (getword(word, sizeof word, stdin) != EOF){
        htable_insert(h, word);
    }
    
    end_1 = clock();

    /** If printTable > 0, prints contents of table, the words and freqs */
    if (printTable){
        htable_print_entire_table(h, stderr);
        htable_print(h, print_info);
    }

    /** Opens file, searches hash table comparing words. Acts as spellcheck */
    if(spellcheck){
        file = open_file(fileName);
        
        start_2 = clock();
        while (getword(word, sizeof word, file) != EOF){
            if (htable_search(h, word) == 0){
                wordsUnknown++;
                fprintf(stdout, "%s\n", word);
            }
        }
        end_2 = clock();

        tableSearch = ((end_2 - start_2) / (double)CLOCKS_PER_SEC);
        tableFill = ((end_1 - start_1) / (double)CLOCKS_PER_SEC);


        fprintf(stderr, "Fill time     : %3f\n", tableFill);
        fprintf(stderr, "Search time   : %3f\n", tableSearch);
        fprintf(stderr, "Unknown words = %d\n", wordsUnknown);

        fclose(file);
        
    }

    /** If printStats & snapshots are both > 0, print stats with snapshot nums*/
    if (printStats && snapshots){
        htable_print_stats(h, stdout, numSnaps);
    }
    else if (printStats){
        numSnaps = 10;
        htable_print_stats(h, stdout, numSnaps);
    }
    else{
        htable_print(h, print_info);
    }

    htable_free(h);
    return EXIT_SUCCESS;
}


    
    
