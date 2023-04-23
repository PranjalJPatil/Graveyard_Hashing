all: test test_2

CC = g++
OPT= -g -flto -Ofast
CFLAGS = $(OPT) -Wall -march=native
LIBS = -lssl -lcrypto 

test: main_timing.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test_2: main_timing_2.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f test test.o
	rm -f test_2 test_2.o