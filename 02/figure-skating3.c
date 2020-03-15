#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 10

int main (void){
    double s1, s2, s3;
    double reg_num;
    double judge1[ARRAY_SIZE];
    double judge2[ARRAY_SIZE];
    double judge3[ARRAY_SIZE];
    int count = 0;
    int i;
    double judge1_total = 0;
    double judge2_total = 0;
    double judge3_total = 0;
    double judge1_avg = 0;
    double judge2_avg = 0;
    double judge3_avg = 0;
    double judge1_dis_sqed = 0;
    double judge2_dis_sqed = 0;
    double judge3_dis_sqed = 0;
    double judge1_sd;
    double judge2_sd;
    double judge3_sd;
    

    while (4 == scanf("%lg%lg%lg%lg", &reg_num, &s1, &s2, &s3)){
        judge1[count] = s1;
        judge2[count] = s2;
        judge3[count] = s3;
        judge1_total += judge1[count];
        judge2_total += judge2[count];
        judge3_total += judge3[count];
        count++;
    }

    judge1_avg = judge1_total/ARRAY_SIZE;
    judge2_avg = judge2_total/ARRAY_SIZE;
    judge3_avg = judge3_total/ARRAY_SIZE;

    for (i = 0; i < ARRAY_SIZE; i++){
        judge1_dis_sqed += (judge1[count]-judge1_avg)*(judge1[count]-judge1_avg);
        judge2_dis_sqed += (judge2[count]-judge2_avg)*(judge2[count]-judge2_avg);
        judge3_dis_sqed += (judge3[count]-judge3_avg)*(judge3[count]-judge3_avg);
    }

    judge1_sd = sqrt(judge1_dis_sqed/(ARRAY_SIZE-1));
    judge2_sd = sqrt(judge2_dis_sqed/(ARRAY_SIZE-1));
    judge3_sd = sqrt(judge3_dis_sqed/(ARRAY_SIZE-1));

    printf("          Average      SD\n");
    printf("Judge 1 : %f     %f\n", judge1_avg, judge1_sd);
    printf("Judge 2 : %f     %f\n", judge2_avg, judge2_sd);
    printf("Judge 3 : %f     %f\n", judge3_avg, judge3_sd);

    return EXIT_SUCCESS;
}
    
    
    
        
        
                                         
        

        
            
        
    
