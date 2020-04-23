### ECSE444 W2020 Final Project (McGill University)

**Setup Instructions**
Download FFTW: http://www.fftw.org/
1. Go here: http://www.fftw.org/download.html
2. Download the tar.gz or any other way listed. Downloading anywhere on your personal computer should be fine
3. Go to the root folder of fftw and run:
```./configure
make
make check
make install
make install check
make clean 
```
**Important**  
To compile any .c script that uses the fftw3 library, you should compile like this on the command line:  
```gcc [filename] -lfftw3 -lm```

**Super Important**  
To run the file "csv_to_array.c" in the helper scripts folder:
Go to the helper scripts folder and run:  
`gcc *.c -lfftw3 -lm`. Then, do `/a.out`

Example Input File: `../data/original/one_Alex1.csv`   
Example Output File: `../data/MFCC/one_Alex1_mfcc`
