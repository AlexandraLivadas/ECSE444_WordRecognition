#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>
#include <math.h>

//#include <libmfcc.h>
#define N 6000

#include "headers/conversions.h"
#include "libmfcc.h"

//fftw_complex *out;
//double *out;
double *mfcc[500][12];
double *mfcc_result;
fftw_plan p;


double *computeFFT(double* input){
    FILE *f_fft;
    f_fft = fopen("../data/FFT/one_Alex1_fft", "wb"); 
    //out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (n/2+1));
    double *out;
    out = (double*) malloc(sizeof(double)*N);
    //in = (double*)input;
    //p = fftw_plan_dft_r2c_1d(n, input, out, FFTW_ESTIMATE);
    //This is a real-to-real FFT with a half-complex format???
    p = fftw_plan_r2r_1d(N, input, out, FFTW_R2HC, FFTW_ESTIMATE);
    for (int i = 0; i < N; i++) 
        input[i] = input[i]/512; //idk

    fftw_execute(p); /* repeat as needed */

    // for (int i = 0; i < N; i++){
    //     fprintf(f_fft, "%d: %lf\n", i, out[i]);
    //     //printf("%lf, ", out[i]);
    // }
    fftw_destroy_plan(p);
    return out;
}

void freeFFT(fftw_complex *out) {
    fftw_free(out);
}

double *csv_to_arr(char *filename){
    FILE *fp;
    double *a = (double*) malloc(sizeof(double)*N);
    size_t count = 0;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }

    while (fscanf(fp, "%lf,", &a[count]) != EOF) {
        //printf("%lf, ", a[count]);
        count++;
    }
    //printf("\n Count: %zu\n", count);

    fclose(fp);

    return a;
}

double *computeMFCC(double *in, int n, int frame_n, FILE *f){
    double *mfcc_result = (double*) malloc(sizeof(double)*n);
    //mfcc_result = (double*) malloc(sizeof(double)*n);

    //Compute the first n coefficients
	for(int coeff = 0; coeff < n; coeff++)
	{
        //If on frame 3 and coeff 4, we would want to calculate the MFCC @ (2*12)+4 (pretty sure)
        int i = coeff+(n*frame_n);
		mfcc_result[coeff] = GetCoefficient(in, 16000, 48, 6000, i); 
        fprintf(f, "%i: %f, og: %lf\n", i, mfcc_result[coeff], in[i]);
		//printf("%i %f, ", i, mfcc_result[coeff]);
	}

    return mfcc_result;
}

