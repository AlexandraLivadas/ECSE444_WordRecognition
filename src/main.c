#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>
#include <math.h>

#define N 6000

#include "headers/conversions.h"

double **getMFCC(char* origin, char *dest){
    double *a = (double*) malloc(sizeof(double)*N);
    a = csv_to_arr(origin);

    double *i = (double*) malloc(sizeof(double)*(N+1));
    i = computeFFT(a);

    FILE *f;
    f = fopen(dest, "wb");
    
    double **mfcc;
    mfcc = (double**)malloc(sizeof(double*)*500);
    //For 6000 inputs, 12 MFCC per frame: 500 frames
    for (int j = 0; j < 4; j++){ //TODO: doesn't calculate beyond 4 frames???
        fprintf(f, "FRAME NUMBER: %d\n", j);
        mfcc[j] = (double*)malloc(sizeof(double*)*12);
        mfcc[j] = computeMFCC(i, 12, j, f);
    }

    fclose(f);

}

int main(void) { 

    char originFile[200];
    char destFile[200];
    printf("Input File: ");
    scanf("%s", originFile);
    printf("Destination File: ");
    scanf("%s", destFile);
    double **mfcc;
    mfcc = (double**)malloc(sizeof(double*)*500);
    mfcc = getMFCC(originFile, destFile);
    
    return 0;
}
