#include <stdio.h>
#include <stdlib.h>

int main (void){
    double s1, s2, s3;
    int return_code;

    return_code = scanf("%lg%lg%lg", &s1, &s2, &s3);

    if (s1 < s2 && s1 < s3){
        printf("(%f + %f)/2", s2, s3);
    } else if (s2 < s3 && s2 < s1){
        printf("(%f + %f)/2", s1, s3);
    } else if (s3 < s2 && s3 < s1){
        printf("(%f + %f)/2", s1, s2);
    }

    return EXIT_SUCCESS;
}
