//
// Created by Bram de Wit on 15/11/2019.
//
// As part of the minor Software for Science, by the Amsterdam univeristy of applied sciences
// Project power monitoring, commissioned by Astron netherlands institute for radio astronomy
//

/* this program uses the FFTW3 library
 * which is FREE software, released under the GNU General Public License (GPL)
 * for more info on FFTW3 go to http://www.fftw.org
 *
 * Also BMP processing relies on bitmap_image.hpp
 * aslo FREE software, released under the MIT license
 * form more information go to http://www.partow.net
 *
 * */

// to compile:
//
// c++ main.cpp samples.h bitmap_image.hpp -pthread -lfftw3_threads -lfftw3 -lm -o main
// or run the makefile 

#include <iostream>
#include <stdio.h>
#include <fftw3.h>
#include "samples.h"
#include "bitmap_image.hpp"
#include <omp.h>
#include <math.h>


#define REAL 0
#define IMAG 1

/* fills an array with a real and imaginary part */
void fill_signal_1d(fftw_complex* signal, double* realpart, double* imaginarypart) {

    int i;
    for (i = 0; i < NUM_POINTS; ++i) {

        signal[i][REAL] = realpart[i];

        signal[i][IMAG] = imaginarypart[i];
    }
}

/* calculates the magnitude of the signal in the frequency domain */
void calc_magnitude(fftw_complex* result) {
    int i;
    for (i = 0; i < NUM_POINTS/2; ++i) {
        double mag = sqrt(result[i][REAL] * result[i][REAL] +
                          result[i][IMAG] * result[i][IMAG]);

        //num points/2 because of nyquist limit
        mag = (mag/NUM_POINTS)*2;
        //filter out noise
        if(mag < 0.0001) mag = 0;

        printf("Freq %i Hz = %g\n", i, mag);
    }
}

/* calulates what the origional samples were
 * from the frequency domain to the time domain*/
void calc_back_to_samples (fftw_complex* result) {

    for(int i = 0; i<NUM_POINTS; i++){

        printf("sample point %i = %g \n",i, result[i][REAL]/NUM_POINTS);

    }

}

/* create bmp file from the input string */
void input_string_to_bmp (double* string){

    int width = WIDTH;
    int height = HEIGHT;
    int i = 0;
    u_int8_t colour;
    bitmap_image image(width, height);
    image.clear();

    image_drawer draw(image);
    draw.pen_width(1);

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){

            colour = (u_int8_t)(string[i]);

            draw.pen_color(colour, colour, colour);
            draw.plot_pixel(w,h);
            i++;
        }
    }

    image.save_image("input_string.bmp");

}


/* creates bmp from the frequency domain output */
void FFT_string_to_bmp (fftw_complex* string){

    int width = WIDTH;
    int height = HEIGHT;
    int i = 0;
    u_int8_t colour;
    bitmap_image image(width, height);
    image.clear();

    image_drawer draw(image);
    draw.pen_width(1);

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){

            double mag = sqrt(string[i][REAL] * string[i][REAL] +
                              string[i][IMAG] * string[i][IMAG]);

            colour = (u_int8_t)(mag);

            draw.pen_color(colour, colour, colour);
            draw.plot_pixel(w,h);

            i++;
        }
    }

    image.save_image("processed_string_frequency_domain.bmp");
}


/* creates bmp from the string converted back to the time domain */
void IFFT_string_to_bmp (fftw_complex* string){

    int width = WIDTH;
    int height = HEIGHT;
    int i = 0;
    u_int8_t colour;
    bitmap_image image(width, height);
    image.clear();

    image_drawer draw(image);
    draw.pen_width(1);

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){

            colour = (u_int8_t)(string[i][REAL]/NUM_POINTS);

            draw.pen_color(colour, colour, colour);
            draw.plot_pixel(w,h);
            i++;
        }
    }
    image.save_image("processed_string_time_domain.bmp");

}


int main(int argc, char **argv) {

    /* create bmp file from input string */
    input_string_to_bmp(real_part);

    /*arrays with a real and imaginary part*/
    fftw_complex signal[NUM_POINTS];
    fftw_complex result[NUM_POINTS];
    fftw_complex iresult[NUM_POINTS];

    /* fill an array with data  */
    fill_signal_1d(signal, real_part, imaginary_part);

    /*check if argument is given*/
    if(argc < 2){ 
        printf("missing argument, argument is for setting amount of threads\n\r"); 
        return 1; 
    }

    /* setup for multithreading*/
    fftw_init_threads();
    fftw_plan_with_nthreads(atoi(argv[1]));

    /* create plan for time domain to freq domain  */
    fftw_plan plan = fftw_plan_dft_2d(WIDTH,
                                      HEIGHT,
                                      signal,
                                      result,
                                      FFTW_FORWARD,
                                      FFTW_ESTIMATE);

    /* create plan for freq domain back to time */
    fftw_plan iplan = fftw_plan_dft_2d(WIDTH,
                                       HEIGHT,
                                       result,
                                       iresult,
                                       FFTW_BACKWARD,
                                       FFTW_ESTIMATE);


    /* execute plans and print the magnitudes */
    fftw_execute(plan);
    calc_magnitude(result);

    /* make bmp from freq domain */
    FFT_string_to_bmp(result);

    fftw_execute(iplan);

    /* make bmp from inverse fft */
    calc_back_to_samples(iresult);
    IFFT_string_to_bmp(iresult);


    /* cleanup memory used */
    fftw_destroy_plan(plan);
    fftw_destroy_plan(iplan);

    fftw_cleanup_threads();

    return 0;
}
