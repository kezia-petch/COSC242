#include <stdio.h>
#include <stdlib.h>

int display_repeats (int *my_array, int array_size){
    int i, j;
    int *my_array2;

    my_array2 = malloc(array_size * sizeof my_array2[0]);
    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++){
        my_array2[i] = 0;
    }

    for (i = 0; i < array_size; i++){
        for (j = 0; j < array_size; j++){
            if(my_array[i] == j){
                my_array2[j]++;
            }
        }
    }
    
    for (i = 0; i < array_size; i++){
        if(my_array[i] > 1){
            printf("%d occurs %d times\n", i, my_array[i]);
        }
    }
    
    return EXIT_SUCCESS;
}

int main(void) {
    int array_size = 0;
    int *my_array;
    int i = 0;

    printf("Enter the size of the array: ");
    scanf("%d", &array_size);

    my_array = malloc(array_size * sizeof my_array[0]);
    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++){
        my_array[i] = rand() % array_size;
    }

    printf("What's in the array:\n");
    for (i = 0; i < array_size; i++){
        printf("%d ", my_array[i]);
    }
    printf("\n");
    
    display_repeats(my_array, array_size);
                
    free(my_array);

    return EXIT_SUCCESS;
}

