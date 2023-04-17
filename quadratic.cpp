#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include "hashutil.c"

using namespace std;

struct QuadraticHash{

    long *hashTable;
    long tableSize;
    long tableSeed;
    long maxIterations;
    double loadFactor;
    // vector<long>* hashTablePtr;

    //// Hashing with Qudratic Probing
    QuadraticHash(long initSize, double initLoadFactor, long initSeed, long initMaxIterations){
        hashTable = new long[initSize];
        loadFactor = initLoadFactor;
        tableSize = initSize;
        tableSeed = initSeed;
        maxIterations = initMaxIterations;
        // hashTablesPtr = new vector<long>[2];

    
    }

    void insert(long x){
        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize;

        cout << "The Inserting of Item: " << x << " has hashIndex of: " << hashIndex << endl; 

        for(int i = 0; i < maxIterations; i++){
            if(!hashTable[hashIndex]){
                hashTable[hashIndex] = x;
                return;
            }

            

            long newIndex = (long) (hashIndex + pow((i+1),2)) % tableSize;
            hashIndex = newIndex;

            // hashIndex = (hashIndex + pow((i+1),2)) % tableSize;
        }
    }

    bool lookup(long x){
        // bool foundItem = false;

        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize; 

        cout << "The Lookup of Item: " << x << " has hashIndex of: " << hashIndex << endl; 

        for(int i = 0; i < maxIterations; i++){
            // long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize; 

            if(!hashTable[hashIndex]){
                return false;
            }else{
                if(hashTable[hashIndex]==x){
                    return true;
                }
            }

            long newIndex = (long) (hashIndex + pow((i+1),2)) % tableSize;
            hashIndex = newIndex;
            
            // hashIndex = (hashIndex + pow((double) i,2)) % tableSize;
        }

        return false;

    }

    void resize(long factor){
        long newSize = tableSize * factor;
        long *newHashTable = new long[newSize];
        for(int i = 0; i < tableSize;i++){
            if(hashTable[i]){
                newHashTable[i] = hashTable[i];
            }
        }

        tableSize = newSize;
        delete[] hashTable;
        hashTable = newHashTable;
    }


    void deleteItem(long x){
        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize;
        for(int i = 0; i < maxIterations; i++){

            if(hashTable[hashIndex]){
                if(hashTable[hashIndex]==x){
                    hashTable[hashIndex] = 0;
                    return;
                }
            }
            
            long newIndex = (long) (hashIndex + pow((i+1),2)) % tableSize;
            hashIndex = newIndex;
        }
    }


};