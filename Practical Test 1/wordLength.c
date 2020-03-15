#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s){
    void *result = malloc(s);
    if (NULL == result){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_long_words(char **a, int n, double average){
    if (n > 0){
        if(strlen(a[0]) > average){
        printf("%s\n", a[0]);
        }
        print_long_words(a+1, n-1, average);
    }
}

int main(void){
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    double average, total = 0;
    int num_words, i;

    num_words = 0;

    while(num_words < ARRAY_LEN && 1 == scanf("%79s\n", word)){
        wordlist[num_words] = emalloc((strlen(word) + 1)*sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        total += strlen(word);
        num_words++;
    }

    if (num_words > 0){
    average = (total/num_words);

    print_long_words(wordlist, num_words, average);

    fprintf(stderr, "%.2f\n", average);
    }
    for(i = 0; i < num_words; i++){
        free(wordlist[i]);
    }

    return EXIT_SUCCESS;
}
