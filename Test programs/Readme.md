## 3 test programs for testing the power consumption on our raspberry pi setup

----

### FFT with multithreading 

 The FFT with multithreading is made by the power monitoring team,
 it uses a bitmap library and the fftw library to generate a image from an array 
 this array is also fourier transformed and then inverse fourier transformed 

 each state of the image is converted to bmp so, 
 one before the process, one in the fourier domain and one converted back to the real domain  

 it also uses multithreading, the amount of threads can be given in the arguments 
 
#### Mandelbrot with MPI

 The mandelbrot with MPI
 is a mandelbrot library from the internet 
 
 "this program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version."

 Dynamic MPI Mandelbrot algorithm
 * Copyright (C) 2015  Martin Ohmann <martin@mohmann.de>

It is used to generate a mandelbrot figure using mpi

### FFT with MPI 

The FFT with MPI is an example from the internet aswell,

made by Nathan Smith
<https://github.com/nsmith5/FFTW-MPI-Examples>

it can fourier transform some data with parralel processing using mpi and the FFTW library

### Compilation and execution 

 To compile each file has a makefile 

 To run the mpi programs use " mpiexec -n 'amount of processes' -f machinefile ./'the program' 

 To run the multithreading FFT program use ./FFT_multithread 'amount of threads'
 
 
### licenses 

 Mandelbrot   : GNU General Public License (GPL)  
 FFTW3        : GNU General Public License (GPL)  
 Bitmap image : MIT license