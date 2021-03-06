#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>
#include <math.h>

#define N 6000
#define C 12
#define F 4

//Get distance for one frame (currently returning average distance)
double dist_frame(double* test, double* train){
    //printf("HERE5\n");
    double avDist = 0;
    double sumDist = 0;
    int size = sizeof(test)/sizeof(test[0]);
    for (int i = 0; i < size; i++){
        sumDist = sumDist + (test[i]-train[i])*(test[i]-train[i]);
    }
    avDist = sumDist/size;
    return avDist;
}

double getMin(double a, double b, double c){
    if (a <= b && a <= c){
        return a;
    }
    else if (b <= a && b <= c){
        return b;
    }
    else {
        return c;
    }
}

double getDTW(double** test, double** train, int i, int j){

    //DTW[0][0] = just the initial dist (I think)
    if (i == 0 && j == 0){
        return dist_frame(test[i], train[j]);
        //return 0;
    }
    //DTW[0][j] and DTW[i][0] (so first column/row) should be infinity?
    // else if ((i = 0 && j > 0) || (j == 0 && i > 0)){
    //     return INFINITY;
    // }
    //If first row
    else if (i = 0 && j > 0){
        return dist_frame(test[i], train[j]) + getDTW(test, train, i, j-1);
    }
    //If first col
    else if (j = 0 && i > 0){
        return dist_frame(test[i], train[j]) + getDTW(test, train, i-1, j);
    } 
    else {
        return (dist_frame(test[i], train[j]) + min(
            getDTW(test, train, i-1, j), getDTW(test, train, i-1, j-1), getDTW(test, train, i, j-1)));
    }

}
// //Gets DTW distance between two MFCC double** arrays?
// double getDTWDist(double** test, double** train){
//     //printf("HERE2\n");
//     double** Dist;
//     Dist = (double**) malloc(sizeof(double*)*F);
//     //printf("HERE6\n");
//     //Get local distance: (change F to number of frames (4 for now))
//     for (int i = 0; i < F; i++){
//         //printf("HERE7\n");
//         Dist[i] = (double*) malloc(sizeof(double)*F);
//         for (int j = 0; j < F; j++){
//             //printf("HERE8\n");
//             Dist[i][j] = dist_frame(test[i], train[j]); //??????
//         }
//     }

//     //Now what?
//     //Have to make the D[F][F] matrix?
//     // D(i, j) = Dist(i, j) + min(D(i-1, j), D(i-1, j-1), D(i, j-1));
//     // So D(0, 0) = Dist(i, j)
//     // first row: D(0, j) = Dist(0, j) + D(i, j-1) ***from j = 1
//     // first column: D(i, 0) = Dist(i, 0) + D(i-1, j) **from i = 1
//     // then continue from there 
//     //printf("HERE3\n");
//     double **D;
//     D = (double**) malloc(sizeof(double*)*F);
//     D[0] = (double*) malloc(sizeof(double)*F);
//     //printf("HERE20\n");
//     D[0][0] = Dist[0][0];

//     //Fill first row:
//     for (int j = 1; j < F; j++){
//         //printf("HERE30\n");
//         D[j] = (double*) malloc(sizeof(double)*F);
//         D[j][0] = Dist[j][0] + D[j-1][0];
//     }
//     //Fill first column:
//     for (int i = 1; i < F; i++){
//         //D[i] = (double*) malloc(sizeof(double)*F);
//         //printf("HERE40\n");
//         D[0][i] = Dist[0][i] + D[0][i-1];
//     }
//     //Fill the rest (starting from 1?):
//     for (int k = 1; k < F; k++){
//         for (int l = 1; l < F; l++){
//             //printf("%d, %d", k, l);
//             D[k][l] = Dist[k][l] + getMin(D[k-1][l], D[k-1][l-1], D[k][l-1]);
//             //printf("HERE46\n");
//         }
//     }

//     //printf("HERE4\n");
//     return D[F-1][F-1];
// }
