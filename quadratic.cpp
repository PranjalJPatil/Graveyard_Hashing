#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include "hashutil.c"

using namespace std;

/* 
 Struct for hashing with quadratic probing 
 */
struct QuadraticHash{
    long *hashTable;       //// Array for hashtable     
    long tableSize;        //// Table size
    long tableBaseSize;    
    long tableSeed;        //// Seed for table
    long maxIterations;    //// Maximum number of iterations 
    double loadFactor;      
    long numberOfElements;
    double enlargeFactor;
    long maxCollisions;

    //// Initializing Class
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

    //// Insert an item x into the hash table
    void insert(long x){
        long hashIndex = (long) (MurmurHash64A(&x,sizeof(long),tableSeed) % tableSize);

        //// If item exists, stop there
        if(lookup(x)){
            return;
        }

        
        int counter = 0;
        int numOfCollisions = 0;
        int numOfIterations = 0;

        long insert_val = x;

        //// If the collision exists and the number of iterations is well below the limit, keep looping
        while(hashTable[hashIndex] && numOfIterations <= maxIterations){
            long oldItem = hashTable[hashIndex];
            //// Position of next index without modular 
            long nextIndex =  (hashIndex + pow((counter+1),2));
            //// New index after modular calculation 
            long newIndex = (long) (nextIndex % tableSize);

            hashIndex = newIndex;
            counter++;

            numOfCollisions++;

            if(numOfCollisions > maxCollisions){
                maxCollisions = numOfCollisions;
            }

            //// If the index succeeds the table size, increases the number of iterations
            if(nextIndex >= tableSize){
                numOfIterations++;
            }
            
            //// Swap the item to be inserted with the old item
            hashTable[hashIndex] = insert_val;
            insert_val = oldItem;
        }

        //// If an empty spot if found, the value is going to be inserted.
        if(hashTable[hashIndex]==0){
            hashTable[hashIndex] = insert_val;
        }

        //// If the number of iterations doesn't succeed maximum number of iterations, 
        //// increase the number of elements.
        if(numOfIterations <= maxIterations){
            numberOfElements++;
        }

    }

    //// Function for lookup 
    bool lookup(long x){
        long hashIndex = (long) (MurmurHash64A(&x,sizeof(long),tableSeed) % tableSize); 
        long counter = 0;
        long numOfCollisions = 0;
        long numOfIterations = 0;

        //// If the collision exists and the number of iterations is well below the limit, keep looping
        while(hashTable[hashIndex] && numOfIterations < maxIterations){
            if(hashTable[hashIndex]==x){
                return true;
            }
            long nextIndex =  (hashIndex + pow((counter+1),2));
            long newIndex = (long) (nextIndex % tableSize);
            counter++;
            hashIndex = newIndex;
            numOfCollisions++;

            if(nextIndex>=tableSize){
                numOfIterations++;
            }
        }

        return false;
    }

     //// Function for delete items
    void deleteItem(long x){
        long hashIndex = MurmurHash64A(&x,sizeof(long),tableSeed) % tableSize;

        int counter = 0;
        int numOfCollisions = 0;
        int numOfIterations = 0;

        //// If the collision exists and the number of iterations is well below the limit, keep looping
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

            if(nextIndex >= tableSize){
                numOfIterations++;
            }
        }

    }

    //// Printing to debug items
    void print(){
        cout << " Start printing ------ " << endl;
        for(int i = 0; i < tableSize; i++){
            cout << "The current value of hash table at index " << i << " is: " << hashTable[i] << endl;
        }
    }

    //// Get the number of elements
    long numOfElements(){
        return numberOfElements;
    }


};