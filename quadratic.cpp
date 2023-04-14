#include <iostream>
#include <vector>
#include <math.h>
#include "hashutil.c"

using namespace std;

struct QuadraticHash{

    long *hashTable;
    long tableSize;
    long tableSeed;
    long maxIterations;

    //// Hashing with Qudratic Probing
    QuadraticHash(long initSize, long initSeed, long initMaxIterations){
        hashTable = new long[initSize];
        tableSize = initSize;
        tableSeed = initSeed;
        maxIterations = initMaxIterations;
    }

    void insert(long x){
        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize;

        for(int i = 0; i < maxIterations; i++){

            if(hashTable[hashIndex]==0){
                return;
            }

            hashIndex = (hashIndex + pow((i+1),2)) % tableSize;
        }

    }


    bool lookup(long x){
        // bool foundItem = false;

        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize; 

        for(int i = 0; i < maxIterations; i++){
            // long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize; 

            if(hashTable[hashIndex]==0){
                return false;
            }else{
                if(hashTable[hashIndex]==x){
                    return true;
                }
            }
            
            hashIndex = (hashIndex + pow((i+1),2)) % tableSize;
        }

        return false;

    }


};