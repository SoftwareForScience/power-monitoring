cmake_minimum_required(VERSION 3.15)
project(FFTW3)

set(CMAKE_CXX_STANDARD 17)

set(MY_CXX_FLAGS ${MY_CXX_FLAGS} "-lifftw -lfftw3 -lm")


add_executable(FFTW3 main.cpp samples.h)

