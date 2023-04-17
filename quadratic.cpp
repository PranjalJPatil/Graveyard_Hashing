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

    
    }

    void insert(long x){
        long hashIndex = MurmurHash64A(&x,tableBaseSize,tableSeed) % tableBaseSize;

        // cout << "The murmur hash is: " << MurmurHash64A(&x,tableSize,tableSeed) << endl;

        cout << "The Inserting of Item: " << x << " has hashIndex of: " << hashIndex << endl; 

        int counter = 0;

        while(hashTable[hashIndex]){
            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableBaseSize;
            hashIndex = newIndex;
            counter++;
        }

        hashTable[hashIndex] = x;
        numberOfElements++;

        if(numberOfElements >= (long)(loadFactor * tableSize)){
            resize(enlargeFactor);
        }

    }

    bool lookup(long x){
        // bool foundItem = false;

        long hashIndex = MurmurHash64A(&x,tableBaseSize,tableSeed) % tableBaseSize; 

        long counter = 0;

        cout << "The Lookup of Item: " << x << " has hashIndex of: " << hashIndex << endl; 
        while(hashTable[hashIndex]){
            if(hashTable[hashIndex]==x){
                return true;
            }
            long newIndex = (long) (hashIndex + pow((counter+1),2)) % tableBaseSize;
            counter++;
            hashIndex = newIndex;
            // counter++;
        }

        // hashTable[hashIndex] = x;
        // numberOfElements++;

        // if(numberOfElements >= (long)(loadFactor * tableSize)){
        //     resize(enlargeFactor);
        // }

        return false;

    }

    void resize(double factor){
        long newSize = tableSize * factor;
        long *newHashTable = new long[newSize];
        for(int i = 0; i < tableSize;i++){
            if(hashTable[i]){
                newHashTable[i] = hashTable[i];
                cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
            }
        }

        tableSize = newSize;
        delete[] hashTable;
        hashTable = newHashTable;

        print();
    }


    void deleteItem(long x){
        long hashIndex = MurmurHash64A(&x,tableBaseSize,tableSeed) % tableBaseSize;
        for(int i = 0; i < maxIterations; i++){

            if(hashTable[hashIndex]){
                if(hashTable[hashIndex]==x){
                    hashTable[hashIndex] = 0;
                    return;
                }
            }
            
            long newIndex = (long) (hashIndex + pow((i+1),2)) % tableBaseSize;
            hashIndex = newIndex;
        }
    }

    void print(){
        cout << " Start printing ------ " << endl;
        for(int i = 0; i < tableSize; i++){
            cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
        }
    }


};