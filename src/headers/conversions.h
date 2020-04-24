
//Calculate the FFT values of a given double input array
double *computeFFT(double* input);

//Free the FFT array (uses logic from FFTW3 library)
void freeFFT(fftw_complex *out);

//Converts a CSV file (from MATLAB script) to an array of double values
double *csv_to_arr(char *filename);

/* Compute MFCC values
 * in = double input array (of FFT values)
 * n = number of values in 1 frame
 * frame_n = the current frame number
 * f = file we are writing the results to. 
*/
double *computeMFCC(double *in, int n, int frame_n);

