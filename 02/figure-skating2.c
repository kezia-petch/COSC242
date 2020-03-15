#include <stdio.h>
#include <stdlib.h>

int main (void){
    double s1, s2, s3;
    int reg_num;
    int temp = 0;
    int maximum_num = 0;
    int winner = -1;
    
    while (4 == scanf("%d%lg%lg%lg", &reg_num, &s1, &s2, &s3)){
        if (s1 < s2 && s1 < s3){
            temp = (s2 + s3)/2;
        } else if (s2 < s3 && s2 < s1){
            temp = (s1 + s3)/2;
        } else if (s3 < s2 && s3 < s1){
            temp = (s2 + s1)/2;
        }

        if (temp > maximum_num){
            maximum_num = temp;
            winner = reg_num;
        } 
    }

    printf("%d", winner);
    return EXIT_SUCCESS;
}
