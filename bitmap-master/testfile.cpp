#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include "bitmap_image.hpp"

using namespace std;

int sample() {
    int result;
    FILE * size;
    char value;
    size = fopen ("value.txt", "r");
    string lines;
    while(1){
        value = fgetc(size);
        if( feof(size) ) {
            break ;
        }
        else{
            switch (value){
                case '\n':
                    break;
                default:
                    lines += value;
                    break;
            }
        }
        result = atoi( lines.c_str());
    }
    return result;
}


int main() {

    FILE * gray;
    int n = sample();
    printf("%d", n);
    char sample[n];
    char host;
    int end = 0;
    int separate = 0;
    int width = 0;
    int height = 0;
    int i = 0;
    int x = 0;
    string line;


    gray = fopen ("graycm.txt", "r");
    while(1) {
        host = fgetc(gray);
        if( feof(gray) ) {
            break ;
        }
        else{
            switch (host){
                case '[':
                    break;
                case ']':
                    separate++;
                    end++;
                    sscanf(line.c_str(), "%d", &x);
                    sample[separate] = x;
                    line.clear();
                    break;
                case ',':
                    separate++;
                    break;
                case '\n':
                    break;
                case ' ':
                    sscanf(line.c_str(), "%d", &x);
                    sample[separate] = x;
                    line.clear();
                    break;
                default:
                    line += host;
                    break;
            }
           // printf("%d\n", end);
        }
    }
    printf("%d\n", end);
    printf("%d\n", separate);
    fclose(gray);

    height = end;
    width = (separate/end);


    u_int8_t colour;
    bitmap_image image(width, height);
    image.clear();

    image_drawer draw(image);
    draw.pen_width(1);

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){

            /* +1 to get rid of negative values in sin wave
             * /2 so max value = 1 then times 0xFF to get
             * values between 0 and 0xFF*/

            colour = (u_int8_t)(sample[i]);

            draw.pen_color(colour, colour, colour);
            draw.plot_pixel(w,h);
            i++;
        }

    }
   // printf("%d\n", colour);
    //printf("%d\n", i);
    image.save_image("input_string.bmp");



    return(0);
}