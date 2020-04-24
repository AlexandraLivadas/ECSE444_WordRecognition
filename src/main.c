#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>
#include <math.h>

#define N 6000
#define F 4

#include "headers/main.h"
#include "headers/conversions.h"
#include "headers/dtw.h"

double **getMFCC(char* origin, char *dest){
    double *a = (double*) malloc(sizeof(double)*N);
    a = csv_to_arr(origin);

    double *i = (double*) malloc(sizeof(double)*(N+1));
    i = computeFFT(a);

    FILE *f;
    f = fopen(dest, "wb");
    
    double **mfcc;
    mfcc = (double**)malloc(sizeof(double*)*F);
    //For 6000 inputs, 12 MFCC per frame: 500 frames
    for (int j = 0; j < F; j++){ //TODO: doesn't calculate beyond 4 frames???
        fprintf(f, "FRAME NUMBER: %d\n", j);
        mfcc[j] = (double*)malloc(sizeof(double*)*12);
        mfcc[j] = computeMFCC(i, 12, j, f);
    }

    fclose(f);
    return mfcc;
}

int main(void) { 

    char originFile[200];
    char destFile[200];
    printf("Input Training File: ");
    scanf("%s", originFile);
    printf("Destination Training File: ");
    scanf("%s", destFile);
    double **mfccTrain;
    mfccTrain = (double**) malloc(sizeof(double*)*F);
    mfccTrain = getMFCC(originFile, destFile);
    
    char originTestFile[200];
    char destTestFile[200];
    printf("Input Test File: ");
    scanf("%s", originTestFile);
    printf("Destination Test File: ");
    scanf("%s", destTestFile);
    double **mfccTest;
    mfccTest = (double**) malloc(sizeof(double*)*F);
    mfccTest = getMFCC(originTestFile, destTestFile);

    // printf("HERE16\n");
    // for (int i = 0; i < F; i++){
    //     for (int j = 0; j < F; j++){
    //         printf("%lf, ", mfccTest[i][j]);
    //     }
    // }
    //printf("HERE\n");
    double dist;
    dist = getDTWDist(mfccTrain, mfccTest);
    printf("DTW dist: %lf\n", dist);
    return 0;
}
