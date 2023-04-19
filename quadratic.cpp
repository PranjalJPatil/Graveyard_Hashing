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
    // vector<long>* hashTablePtr;

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
        
        long hashIndex = MurmurHash64A(&x,tableBaseSize,tableSeed) % tableSize;

        // cout << "The Inserting of Item: " << x << " has hashIndex of: " << hashIndex << endl; 

        int counter = 0;
        int numOfCollisions = 0;

        while(hashTable[hashIndex]){
            // cout << "The hashIndex is: " << hashIndex << endl;
            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableSize;
            hashIndex = newIndex;
            counter++;

            numOfCollisions++;

            if(numOfCollisions > maxCollisions){
                maxCollisions = numOfCollisions;
            }
        }

        hashTable[hashIndex] = x;
        numberOfElements++;

        if(numberOfElements >= (long)(loadFactor * tableSize)){
            resize(enlargeFactor);
        }

    }

    bool lookup(long x){
        // cout << "The look up starts: " << endl;
        // long hashIndex = MurmurHash64A(&x,tableBaseSize,tableSeed) % tableBaseSize; 
        // long counter = 0;
        // long numOfCollisions = 0;

        // cout << "The Lookup of Item: " << x << " has hashIndex of: " << hashIndex << endl; 
        // while(hashTable[hashIndex]){
        //     if(numOfCollisions >  maxCollisions){
        //         break;
        //     }

        //     if(hashTable[hashIndex]==x){
        //         return true;
        //     }
        //     long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableBaseSize;
        //     counter++;
        //     hashIndex = newIndex;
        //     numOfCollisions++;
        //     // counter++;
        // }

        return false;
    }

    void resize(double factor){
        // cout << "Resized--------" << endl;
        long newSize = tableSize * factor;
        long *newHashTable = new long[newSize];
        for(int i = 0; i < tableSize;i++){
            if(hashTable[i]){
                newHashTable[i] = hashTable[i];
                // cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
            }
        }

        tableSize = newSize;
        delete[] hashTable;
        hashTable = newHashTable;

        // print();
    }

    void deleteItem(long x){
        long hashIndex = MurmurHash64A(&x,tableBaseSize,tableSeed) % tableSize;

        int counter = 0;
        int numOfCollisions = 0;

        while(hashTable[hashIndex]){
            if(numOfCollisions >  maxCollisions){
                break;
            }

            if(hashTable[hashIndex]==x){
                hashTable[hashIndex] = 0;
                numberOfElements--;
            }

            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableSize;
            hashIndex = newIndex;
            counter++;
            numOfCollisions++;
        }

    }

    void print(){
        cout << " Start printing ------ " << endl;
        for(int i = 0; i < tableSize; i++){
            cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
        }
    }


};