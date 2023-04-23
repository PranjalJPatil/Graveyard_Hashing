#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include "hashutil.c"

using namespace std;

struct QuadraticHash{
    long *hashTable;
    long tableSize;
    long tableBaseSize;
    long tableSeed;
    long maxIterations;
    double loadFactor;
    long numberOfElements;
    double enlargeFactor;
    long maxCollisions;

    //// Hashing with Qudratic Probing
    QuadraticHash(long initSize, double initLoadFactor, double initEnlargeFactor, long initSeed, long initMaxIterations){
        hashTable = new long[initSize];
        loadFactor = initLoadFactor;
        tableSize = initSize;
        tableBaseSize = tableSize;
        tableSeed = initSeed;
        maxIterations = initMaxIterations;
        numberOfElements = 0;
        enlargeFactor = initEnlargeFactor;
        maxCollisions = 0;
    }

    void insert(long x){
        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize;

        int counter = 0;
        int numOfCollisions = 0;
        int numOfIterations = 0;

        long insert_val = x;

        while(hashTable[hashIndex] && numOfIterations <= maxIterations){
            long oldItem = hashTable[hashIndex];
            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableSize;
            hashIndex = newIndex;
            counter++;

            numOfCollisions++;

            if(numOfCollisions > maxCollisions){
                maxCollisions = numOfCollisions;
            }

            numOfIterations++;
            
            hashTable[hashIndex] = insert_val;
            insert_val = oldItem;
        }

        // hashTable[hashIndex] = insert_val;
        if(numOfIterations <= maxIterations){
            numberOfElements++;
        }
        // numberOfElements++;

        // if(numberOfElements >= (long)(loadFactor * tableSize)){
        //     resize(enlargeFactor);
        // }

    }

    bool lookup(long x){
        cout << "The look up starts: " << endl;
        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize; 
        long counter = 0;
        long numOfCollisions = 0;
        long numOfIterations = 0;

        cout << "The Lookup of Item: " << x << " has hashIndex of: " << hashIndex << endl; 
        while(hashTable[hashIndex] && numOfIterations < maxIterations){
            if(hashTable[hashIndex]==x){
                return true;
            }
            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableSize;
            counter++;
            hashIndex = newIndex;
            numOfCollisions++;
            numOfIterations++;
            // counter++;
        }

        return false;
    }

    // void resize(double factor){
    //     long newSize = tableSize * factor;
    //     long *newHashTable = new long[newSize];
    //     for(int i = 0; i < tableSize;i++){
    //         if(hashTable[i]){
    //             newHashTable[i] = hashTable[i];
    //             // cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
    //         }
    //     }

    //     tableSize = newSize;
    //     delete[] hashTable;
    //     hashTable = newHashTable;
    // }

    void deleteItem(long x){
        long hashIndex = MurmurHash64A(&x,tableSize,tableSeed) % tableSize;

        int counter = 0;
        int numOfCollisions = 0;
        int numOfIterations = 0;

        while(hashTable[hashIndex] && numOfIterations <= maxIterations){
            if(hashTable[hashIndex]==x){
                hashTable[hashIndex] = 0;
                numberOfElements--;
                return;
            }

            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableSize;
            hashIndex = newIndex;
            counter++;
            numOfCollisions++;
            numOfIterations++;
        }

        // if(numOfIterations <= maxIterations){
        //     numberOfElements--;
        // }

    }

    void print(){
        cout << " Start printing ------ " << endl;
        for(int i = 0; i < tableSize; i++){
            cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
        }
    }


};