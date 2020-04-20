#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>
#include <math.h>

//#include <libmfcc.h>
#define N 6000

#include "libmfcc.h"

//fftw_complex *out;
double *out;
fftw_plan p;


double *computeFFT(double* input){
    FILE *f_fft;
    f_fft = fopen("../data/FFT/one_Alex1_fft", "wb"); 
    int n = N+1;
    //out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (n/2+1));
    out = (double*) malloc(sizeof(double)*n);
    //in = (double*)input;
    //p = fftw_plan_dft_r2c_1d(n, input, out, FFTW_ESTIMATE);
    //This is a real-to-real FFT with a half-complex format???
    p = fftw_plan_r2r_1d(n, input, out, FFTW_R2HC, FFTW_ESTIMATE);
    for (int i = 0; i < N; i++) 
        input[i] = input[i]/512; //idk

    fftw_execute(p); /* repeat as needed */

    for (int i = 0; i < n; i++){
        fprintf(f_fft, "%lf, ", out[i]);
        printf("%lf, ", out[i]);
    }

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
        printf("%lf, ", a[count]);
        count++;
    }
    printf("\n Count: %zu\n", count);

    fclose(fp);

    return a;
}

double *computeMFCC(double *in, int n){
    FILE *f;
    f = fopen("../data/MFCC/one_Alex1_mfcc", "wb");
    double *mfcc_result = (double *) malloc(sizeof(double)*n);

    if (f == NULL){
        printf("Error: file does not exist");
        exit(1);
    }
    //Compute the first n coefficients
	for(int coeff = 0; coeff < n; coeff++)
	{
		mfcc_result[coeff] = GetCoefficient(in, 16000, 48, 182, coeff);
        fprintf(f, "%i: %f, og: %lf\n", coeff, mfcc_result[coeff], in[coeff]);
		printf("%i %f, ", coeff, mfcc_result[coeff]);
	}
    fclose(f);
    return mfcc_result;
}

int main(void) {
    double *a = (double*) malloc(sizeof(double)*N);
    a = csv_to_arr("../data/original/one_Alex1.csv");

    computeFFT(a);

    fftw_destroy_plan(p);

    double *mfcc = (double*) malloc(sizeof(double)*(N+1));
    mfcc = computeMFCC(out, 4096);
    
    return 0;
}
