cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME FFTW3)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(MY_CXX_FLAGS ${MY_CXX_FLAGS} "-lfftw3_mpi -lmpich -pthread -lfftw3_threads -lfftw3 -lm ")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp bitmap_image.hpp)

target_link_libraries(${PROJECT_NAME} fftw3_mpi mpich fftw3_threads fftw3 Threads::Threads)