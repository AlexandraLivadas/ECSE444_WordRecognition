#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>
#include <math.h>

#define N 6000
#define C 12
#define F 4

//Gets DTW distance between two MFCC double** arrays?
double dist(double** test, double** train){
    double **Dist;
    Dist = (double**) malloc(sizeof(double*)*F);
    //Get local distance: (change F to number of frames (4 for now))
    for (int i = 0; i < F; i++){
        Dist[i] = (double*) malloc(sizeof(double)*F);
        for (int j = 0; j < F; j++){
            Dist[i][j] = dist_frame(test[i], train[j]); //??????
        }
    }

    //Now what?
    //Have to make the D[F][F] matrix?
    // D(i, j) = Dist(i, j) + min(D(i-1, j), D(i-1, j-1), D(i, j-1));
    // So D(0, 0) = Dist(i, j)
    // first row: D(0, j) = Dist(0, j) + D(i, j-1) ***from j = 1
    // first column: D(i, 0) = Dist(i, 0) + D(i-1, j) **from i = 1
    // then continue from there 
    double **D;
    D = (double**) malloc(sizeof(double*)*F);
    D[0] = (double*) malloc(sizeof(double)*F);
    D[0][0] = Dist[0][0];

    //Fill first row:
    for (int j = 1; j < F; j++){
        D[0][j] = Dist[0][j] + D[0][j-1];
    }
    //Fill first column:
    for (int i = 1; i < F; i++){
        D[i] = (double*) malloc(sizeof(double)*F);
        D[i][0] = Dist[i][0] + D[i-1][0];
    }
    //Fill the rest (starting from 1?):
    for (int i = 1; i < F; i++){
        for (int j = 1; j < F; i++){
            D[i][j] = Dist[i][j] + min(D[i-1][j], D[i-1][j-1], D[i][j-1]);
        }
    }

    return 0;
}


//Get distance for one frame?
double dist_frame(double *test, double *train){
    double dist = 0;
    for (int i = 0; i < 12; i++){
        dist = dist + (test[i]-train[i])*(test[i]-train[i]);
    }
    return dist;
}