/* 
  Timing experiments for Cuckoo Hashing with quadratic probing
 */


#include <iostream>
#include <set>
#include <chrono>
#include <openssl/rand.h>
#include "cuckoohashing.cpp"

using namespace std::chrono;

double elapsed(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2) {
	return (duration_cast<duration<double>>(t2 - t1)).count();
}

void safe_rand_bytes(unsigned char *v, uint32_t n) {
	while (n > 0) {
		size_t round_size = n >= INT_MAX ? INT_MAX - 1 : n;
		RAND_bytes(v, round_size);
		v += round_size;
		n -= round_size;
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Specify the number of items for the test.\n";
		exit(1);
	}
	uint32_t N = atoi(argv[1]); 	// number of items

	// Generate N numbers to insert
	uint32_t *in_numbers = (uint32_t *)malloc(N * sizeof(uint32_t));
	if(!in_numbers) {
		std::cerr << "Malloc in_numbers failed.\n";
		exit(0);
	}
	safe_rand_bytes((unsigned char *)in_numbers, sizeof(*in_numbers) * N);

	// Generate N numbers for querying successor
	uint32_t *out_numbers = (uint32_t *)malloc(N * sizeof(uint32_t));
	if(!out_numbers) {
		std::cerr << "Malloc out_numbers failed.\n";
		exit(0);
	}
	safe_rand_bytes((unsigned char *)out_numbers, sizeof(*out_numbers) * N);
	// high_resolution_clock::time_point t1, t2;


	// Generate N numbers for deleting numbers
	uint32_t *delete_numbers = (uint32_t *)malloc(N * sizeof(uint32_t));
	if(!out_numbers) {
		std::cerr << "Malloc out_numbers failed.\n";
		exit(0);
	}
	safe_rand_bytes((unsigned char *)delete_numbers, sizeof(*delete_numbers) * N);
	high_resolution_clock::time_point t1, t2;


	long size = 10;
    double loadFactor = 0.9;
    double enLargeFactor = 2.0;
    long seed = 20;
    long maxIterations = 1000;
	long numOfTests = 7;
    long table1Seed = 30;
    long table2Seed = 40;
	
	for(int i = 0; i < numOfTests;i++){
		cout << "Test with the maximum number of iterations: " << maxIterations << endl;

		CuckooHash ch(size, maxIterations, enLargeFactor, loadFactor, size, size, table1Seed, table2Seed);

		t1 = high_resolution_clock::now();
		for (uint32_t i = 0; i < N; ++i) {
			ch.insert(in_numbers [i]);
		}
		t2 = high_resolution_clock::now();
		std::cout << "Time to insert " + std::to_string(N) + " items: " + std::to_string(elapsed(t1, t2)) + " secs\n";


		t1 = high_resolution_clock::now();
		for (uint32_t i = 0; i < N; ++i) {
			ch.lookup(out_numbers[i]);
		}
		t2 = high_resolution_clock::now();
		std::cout << "Time to lookup " + std::to_string(N) + " items: " + std::to_string(elapsed(t1, t2)) + " secs\n";


		t1 = high_resolution_clock::now();
		for (uint32_t i = 0; i < N; ++i) {
			ch.deleteItem(delete_numbers[i]);
		}
		t2 = high_resolution_clock::now();
		std::cout << "Time to delete " + std::to_string(N) + " items: " + std::to_string(elapsed(t1, t2)) + " secs\n";

		maxIterations = maxIterations * 2;

	}


  
	


    // Test hash table with quadratic probing

	


	return 0;
}
