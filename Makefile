all: test test_2 test_standard

CC = g++
OPT= -g -flto -Ofast
CFLAGS = $(OPT) -Wall -march=native
LIBS = -lssl -lcrypto 


test_standard: test.cc
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test: main_timing.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test_2: main_timing_2.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f test test.o
	rm -f test_2 test_2.o
	rm -f test_standard test_standard.o
