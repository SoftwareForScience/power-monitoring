CC = c++
CFLAGS= -Wall
LIBS= samples.h bitmap_image.hpp -pthread -lfftw3_threads -lfftw3 -lm

FFT_multithread: FFT_multithread.cpp FFT_multithread.o
	$(CC) FFT_multithread.o $(CFLAGS) $(LIBS) -o FFT_multithread

FFT_multithread.o: FFT_multithread.cpp
	$(CC) -c FFT_multithread.cpp $(CFLAGS) -o FFT_multithread.o

.PHONY: clean

clean:
	rm FFT_multithread.o
	rm FFT_multithread
