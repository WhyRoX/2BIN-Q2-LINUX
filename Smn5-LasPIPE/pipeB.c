#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#include "utils.h"

void child(void* arg1, void* arg2){
    int *pipeCL = arg1;
    int *pipeTR = arg2;

    sclose(pipeCL[1]);
    sclose(pipeTR[0]);
    
    int val;
    int sum = 0;
    double avg;
    int count = 0;

    while(sread(pipeCL[0], &val, sizeof(int))) {
        sum += val;
        count++;
        nwrite(pipeTR[1], &sum, sizeof(int));
    }
    avg = (double)sum / count;
    nwrite(pipeTR[1], &avg, sizeof(double));

    sclose(pipeCL[0]);
    sclose(pipeTR[1]);
}

int main(int argc, char **argv) {
    int pipeCL[2];
    spipe(pipeCL);
    
    int pipeTR[2];
    spipe(pipeTR);

    fork_and_run2(child, pipeCL, pipeTR);

    sclose(pipeCL[0]);
    sclose(pipeTR[1]); 

    printf("One int/line: \n");
    int val;
    int sum = 0;
    while (scanf("%d",&val) != EOF) {
        nwrite(pipeCL[1], &val, sizeof(int));
        sread(pipeTR[0], &sum, sizeof(int));
      
        printf("sum = %d\n", sum);
    } 

    sclose(pipeCL[1]);

    double avg;
    sread(pipeTR[0], &avg, sizeof(double));

    printf("\n avg is = %.2f\n", avg);

    sclose(pipeTR[0]);
}