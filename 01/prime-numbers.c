#include <stdio.h>
#include <stdlib.h>

int is_prime(int candidate){
    int i;
    for (i = 2; i < candidate; i++){
        if (candidate % i == 0){
            return 0;
        }
    }
    return 1;
}

int  main (void){
    int candidate = 2;
    int num_printed = 0;
    int count = 0;
    while (num_printed < 200){
        if (is_prime(candidate)){
            printf("%5d", candidate);
            count++;
        }
        if (count % 10 == 0 && is_prime(candidate)){
            (printf("\n"));
        }
        num_printed++;
        candidate++;
    }
    printf("\n");
    return EXIT_SUCCESS;
}
