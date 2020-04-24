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

double **getMFCC(char* origin){
    double *a = (double*) malloc(sizeof(double)*N);
    a = csv_to_arr(origin);

    double *i = (double*) malloc(sizeof(double)*(N+1));
    i = computeFFT(a);

    //FILE *f;
    //f = fopen(dest, "wb");
    
    double **mfcc;
    mfcc = (double**)malloc(sizeof(double*)*F);
    //For 6000 inputs, 12 MFCC per frame: 500 frames
    for (int j = 0; j < F; j++){ //TODO: doesn't calculate beyond 4 frames???
        //fprintf(f, "FRAME NUMBER: %d\n", j);
        mfcc[j] = (double*)malloc(sizeof(double*)*12);
        mfcc[j] = computeMFCC(i, 12, j);
    }

    //fclose(f);
    return mfcc;
}

int main(void) { 

    // char originFile[200];
    // //char destFile[200];
    // printf("Input Training File: ");
    // scanf("%s", originFile);
    // //printf("Destination Training File: ");
    // //scanf("%s", destFile);
    // double **mfccTrain;
    // mfccTrain = (double**) malloc(sizeof(double*)*F);
    // mfccTrain = getMFCC(originFile);
    
    char originTestFile[200];
    //char destTestFile[200];
    printf("Input Test File: ");
    scanf("%s", originTestFile);
    //printf("Destination Test File: ");
    //scanf("%s", destTestFile);
    double **mfccTest;
    mfccTest = (double**) malloc(sizeof(double*)*F);
    mfccTest = getMFCC(originTestFile);

    //Count the plus distances:
    FILE* f_plus;
    f_plus = fopen("training_plus", "rb");
    if (f_plus == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }

    printf("HERE23\n");
    char *filename;
    filename = (char*) malloc(sizeof(char)*200);
    double avePlusDist = 0;
    double sumPlusDist = 0;
    double **mfccTrain;
    mfccTrain = (double**) malloc(sizeof(double*)*F);
    //printf("HERE12\n");
    //while (fscanf(f_plus, "%s\n", filename) != EOF) {
    while (fscanf(f_plus, "%s\n", filename) != EOF){
        //printf("HERE1\n");
        printf("%s, ", filename);
        //count++;
        mfccTrain = getMFCC(filename);
        double dist = getDTWDist(mfccTrain, mfccTest);
        printf("%lf\n", dist);
        sumPlusDist = sumPlusDist + dist;
    }
    avePlusDist = sumPlusDist/20;
    printf("Plus Sum Distance: %lf\n", sumPlusDist);
    printf("Plus Ave Distance: %lf\n", avePlusDist);


    //Count the one distances:
    FILE* f_one;
    f_one = fopen("training_one", "rb");
    if (f_one == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }
    char* file;
    file = (char*) malloc(sizeof(char)*200);
    double sumOneDist = 0;
    double aveOneDist = 0;
    // double **mfccTrain;
    // mfccTrain = (double**) malloc(sizeof(double*)*F);
    while (fscanf(f_one, "%s\n", file) != EOF) {
        //printf("HERE2\n");
        printf("%s, ", file);
        //count++;
        mfccTrain = getMFCC(file);
        double dist = getDTWDist(mfccTrain, mfccTest);
        printf("%lf\n", dist);
        sumOneDist = sumPlusDist + dist;
    }
    aveOneDist = sumOneDist/20;
    printf("One Sum Distance: %lf\n", sumOneDist);
    printf("One Ave Distance: %lf\n", aveOneDist);

    //Count the two distances:
    FILE* f_two;
    f_two = fopen("training_two", "rb");
    if (f_two == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }
    char* f;
    f = (char*) malloc(sizeof(char)*200);
    double sumTwoDist = 0;
    double aveTwoDist = 0;
    // double **mfccTrain;
    // mfccTrain = (double**) malloc(sizeof(double*)*F);
    while (fscanf(f_two, "%s\n", f) != EOF) {
        //printf("HERE3\n");
        printf("%s, ", f);
        //count++;
        mfccTrain = getMFCC(f);
        double dist = getDTWDist(mfccTrain, mfccTest);
        printf("%lf\n", dist);
        sumTwoDist = sumTwoDist + dist;
    }
    aveTwoDist = sumTwoDist/20;
    printf("Two Sum Distance: %lf\n", sumTwoDist);
    printf("Two Ave Distance: %lf\n", aveTwoDist);
    // printf("HERE16\n");
    // for (int i = 0; i < F; i++){
    //     for (int j = 0; j < F; j++){
    //         printf("%lf, ", mfccTest[i][j]);
    //     }
    // }
    //printf("HERE\n");
    //double dist;
    //dist = getDTWDist(mfccTrain, mfccTest);
    //printf("DTW dist: %lf\n", dist);
    return 0;
}
