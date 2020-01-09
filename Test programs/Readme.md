### 3 test programs for testing the power consumption on our raspberry pi setup

## The mandelbrot with MPI is a mandelbrot library from the internet 
## which can generate a mandelbrot with parralel processing using mpi

## The FFT with MPI is an example from the internet aswell 
## it can fourier transform some data with parralel processing using mpi and the fftw library

## The FFT with multithreading is made by the power monitoring team,
## it uses a bitmap library and the fftw library to generate a image from an array 
## this array is also fourier transformed and then inverse fourier transformed 

## each state of the image is converted to bmp so, 
## one before the process, one in the fourier domain and one converted back to the real domain  

## it also uses multithreading, the amount of threads can be given in the arguments 

## To compile each file has a makefile 

## To run the mpi programs use " mpiexec -n 'amount of processes' -f machinefile ./'the program' 

## To run the multithreading FFT program use ./FFT_multithread 'amount of threads' 
