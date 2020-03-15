#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/**
 * A Insertion sort implementation.
 *
 * @author Kezia Somerville-Petch
 */

/**
 * Insertion sort method that moves through the array comparing two
 * values and swapping that values based on value this method also finds
 * where the smallest of the compared values is to be reinserted back into
 * the array.
 *
 * @param *a the array being sorted.
 * @param n array length
 */
void insertion_sort (int *a, int n){
    int p, q, key;
    for (p = 1; p < n; p++){
        key = a[p];
        q = p-1;
        while (q >= 0 && a[q] > key){
            a[q+1] = a[q];
            q = q-1;
        }
        a[q+1] = key;
    }
}

/**
 * Main method.
 * Allows display and comparison of sorting programs.
 *
 * @param void.
 */
int main (void){
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;

    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])){
        count++;
    }
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++){
        printf("%d\n", my_array[i]);
    }
    
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
