import csv
import fftw3 

with open('../data/one_Alex1.csv', 'rb') as csvfile:
    data = list(csv.reader(csvfile))


print(data)
