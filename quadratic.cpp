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
        long hashIndex = (long) (MurmurHash64A(&x,sizeof(long),tableSeed) % tableSize);

        if(lookup(x)){
            return;
        }

        int counter = 0;
        int numOfCollisions = 0;
        int numOfIterations = 0;

        long insert_val = x;

        // cout << "The Insertion of Item: " << x << " has hashIndex of: " << hashIndex << endl; 

        while(hashTable[hashIndex] && numOfIterations <= maxIterations){
            long oldItem = hashTable[hashIndex];
            long nextIndex =  (hashIndex + pow((counter+1),2));
            long newIndex = (long) (nextIndex % tableSize);

            hashIndex = newIndex;
            counter++;

            numOfCollisions++;

            if(numOfCollisions > maxCollisions){
                maxCollisions = numOfCollisions;
            }

            if(nextIndex >= tableSize){
                numOfIterations++;
            }
            
            hashTable[hashIndex] = insert_val;
            insert_val = oldItem;
        }

        if(hashTable[hashIndex]==0){
            hashTable[hashIndex] = insert_val;
        }

        if(numOfIterations <= maxIterations){
            // cout << "Element inserted!!!" << endl;
            numberOfElements++;
        }

    }

    bool lookup(long x){
        // cout << "The look up starts: " << endl;
        long hashIndex = (long) (MurmurHash64A(&x,sizeof(long),tableSeed) % tableSize); 
        long counter = 0;
        long numOfCollisions = 0;
        long numOfIterations = 0;

        // cout << "The Lookup of Item: " << x << " has hashIndex of: " << hashIndex << endl; 
        while(hashTable[hashIndex] && numOfIterations < maxIterations){
            if(hashTable[hashIndex]==x){
                return true;
            }
            long nextIndex =  (hashIndex + pow((counter+1),2));
            long newIndex = (long) (nextIndex % tableSize);
            counter++;
            hashIndex = newIndex;
            numOfCollisions++;
            // long nextIndex =  (hashIndex + pow((counter+1),2));

            if(nextIndex>=tableSize){
                numOfIterations++;
            }
            // counter++;
        }

        // cout << "Lookup doesn't exist!!!" << endl;

        return false;
    }


    void deleteItem(long x){
        long hashIndex = MurmurHash64A(&x,sizeof(long),tableSeed) % tableSize;

        int counter = 0;
        int numOfCollisions = 0;
        int numOfIterations = 0;

        while(hashTable[hashIndex] && numOfIterations <= maxIterations){
            if(hashTable[hashIndex]==x){
                hashTable[hashIndex] = 0;
                numberOfElements--;
                return;
            }

            long nextIndex =  (hashIndex + pow((counter+1),2));     
            long newIndex = (long) nextIndex % tableSize;
            hashIndex = newIndex;
            counter++;
            numOfCollisions++;
            // numOfIterations++;

            if(nextIndex >= tableSize){
                numOfIterations++;
            }
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

    long numOfElements(){
        return numberOfElements;
    }


};