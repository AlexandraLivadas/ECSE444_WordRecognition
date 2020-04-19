#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fftw3.h>

fftw_complex *out;
fftw_plan p;


fftw_complex *computeFFT(double* input, int n){

out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (n/2+1));

//in = (double*)input;
p = fftw_plan_dft_r2c_1d(n, input, out, FFTW_ESTIMATE);
fftw_execute(p); /* repeat as needed */

return out;
}

void freeFFT(fftw_complex *out) {
    fftw_free(out);
}

double *csv_to_arr(char *filename){
    FILE *fp;
    double a[6000];
    size_t count = 0;
    memset(&a, 0, sizeof(a)); 

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

int main(void) {
    
    double *a = csv_to_arr("../data/one_Alex1.csv");

    fftw_complex *out = computeFFT(a, 6000);

    int i;
    for (i = 0; i < 6000 / 2 + 1; i++) {
    printf("out[%d] = {%f, %fi}, ", i, creal(out[i]), cimag(out[i]));
    }

    freeFFT(out);
    fftw_destroy_plan(p);

    return 0;

}
