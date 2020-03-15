#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 30000

/**
 * A Selection sort implementation.
 *
 * @author Kezia Somerville-Petch
 */

/**
 * Selection sort method that that moves through the array to find the minimum value
 * so that it can be placed at the start of the array, allowing sorting to occur.
 *
 * @param *a the array being sorted.
 * @param n array length
 */
void selection_sort (int *a, int n){
    int p, q;
    int temp = 0;
    int min, min_index;
    for (q = 0; q < n-1; q++){
        min = a[q];
        min_index = q;
        for (p = q; p < n; p++){
            temp = a[p];
            if (temp < min){
                min = temp;
                min_index = p;
            }
        }
        temp = a[q];
        a[q] = a[min_index];
        a[min_index] = temp;
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
    selection_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++){
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
