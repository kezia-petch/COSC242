#include <stdio.h>
#include <stdlib.h>

void max_min(int *a, int n, int *max, int *min){
    int i;
    *min = a[0];
    *max = a[0];
    for (i = 0; i < n; i++){
        if (a[i] > *max){
            *max = a[i];
        }
        if (a[i] < *min){
            *min = a[i];
        }
    }
}

int main (void){
    int my_array[] = { 5, 2, 7, 3, 4, 5 };
    int biggest, smallest;
    max_min(my_array, 6, &biggest, &smallest);
    printf("max value is &d, min value is %d\n", biggest, smallest);
    return EXIT_SUCCESS;
}
