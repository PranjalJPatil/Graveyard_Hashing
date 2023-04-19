#include "hashutil.c"
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;


//// Modification Made

//// Hashing
struct CuckooHash{
    vector<int> newElements;
    long** hashTables;
    long tableSize;
    long table1HashLength;
    long table2HashLength;
    long table1Seed;
    long table2Seed;
    long baseSize;
    long totalCapacity;
    long numberOfElements;
    double resizeFactor;
    double loadFactor;
    long maxNumCollisions;

    CuckooHash(long initSize, double initResizeFactor, double initLoadFactor, long initTable1HashLength, long initTable2HashLength, long initTable1Seed, long initTable2Seed){
        hashTables = new long*[2];

        for(int i = 0; i < 2;i++){
            hashTables[i] = new long[tableSize];
        }

        numberOfElements = 0;
        loadFactor = initLoadFactor;
        tableSize = initSize;
        totalCapacity = tableSize * 2;
        baseSize = tableSize;
        resizeFactor = initResizeFactor;
        maxNumCollisions = 0;

        table1Seed = initTable1Seed;
        table2Seed = initTable2Seed;
    }

    void insert(long x){
        if(numberOfElements >= totalCapacity * loadFactor){
            resize();
        }

        bool foundItem = false;

        // if(lookup(x)){
        //     return;
        // }

        long insert_val = x;

        long table1HashIndex = MurmurHash64A(&x,baseSize,table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,baseSize,table2Seed) % tableSize;

        long numOfCollisions = 0;
        long counter = 0;

        while(true){
            if(!hashTables[0][table1HashIndex]){
                hashTables[0][table1HashIndex] = insert_val;
                numberOfElements++;
                break;
            }
            
            long hashTable1Item = hashTables[0][table1HashIndex];
            hashTables[0][table1HashIndex] = insert_val;
            insert_val = hashTable1Item;

            if(!hashTables[1][table2HashIndex]){
                hashTables[0][table2HashIndex] = insert_val;
                numberOfElements++;
                break;
            }

            long hashTable2Item = hashTables[0][table2HashIndex];
            hashTables[0][table2HashIndex] = insert_val;
            insert_val = hashTable2Item;

            table1HashIndex = (long)(table1HashIndex + pow((counter+1),2)) % tableSize; 
            table2HashIndex = (long)(table2HashIndex + pow((counter+1),2)) % tableSize; 

            counter++;
            numOfCollisions++;

            if(maxNumCollisions < numOfCollisions){
                maxNumCollisions = numOfCollisions;
            }
        }
    }

    bool lookup(long x){
        // long insert_val = x;

        // long numOfCollisions = 0;

        // long table1HashIndex = MurmurHash64A(&x,baseSize,table1Seed) % baseSize;
        // long table2HashIndex = MurmurHash64A(&x,baseSize,table2Seed) % baseSize;

        // cout << "The index of item " << x << " at hash table 1 is: " << table1HashIndex << endl;
        // cout << "The index of item " << x << " at hash table 2 is: " << table2HashIndex << endl;

        // long counter = 0;

        // while(numOfCollisions < maxNumCollisions){
        //     if(hashTables[0][table1HashIndex]){
        //         if(hashTables[0][table1HashIndex]==x){
        //             return true;
        //         }
        //     }
            
        //     if(hashTables[1][table2HashIndex]){
        //         if(hashTables[0][table2HashIndex]==x){
        //             return true;
        //         }
        //     }

        //     table1HashIndex = (long)(table1HashIndex + pow((counter+1),2)) % baseSize; 
        //     table2HashIndex = (long)(table2HashIndex + pow((counter+1),2)) % baseSize; 

        //     numOfCollisions++;
        //     counter++;
        // }

        return true;
    }

    void resize(){
        long newSize = tableSize * resizeFactor;
        long** newHashTables = new long*[2];

        for(int i = 0; i < 2;i++){
            newHashTables[i] = new long[newSize];
        }
        
        for(int i = 0; i < 2;i++){
            for(int j = 0; j < tableSize;j++){
                if(hashTables[i][j]){
                    newHashTables[i][j] = hashTables[i][j];
                }
            }
        }

        tableSize = newSize;
        delete[] hashTables;
        hashTables = newHashTables;
        totalCapacity = tableSize * 2;
    }

    void deleteItem(long x){
        // long insert_val = x;
        long numOfCollisions = 0;

        long table1HashIndex = MurmurHash64A(&x,baseSize,table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,baseSize,table2Seed) % tableSize;

        long counter = 0;

        while(numOfCollisions < maxNumCollisions){
            if(hashTables[0][table1HashIndex]){
                if(hashTables[0][table1HashIndex]==x){
                    hashTables[0][table1HashIndex] = 0;
                    break;
                }
            }
            
            if(hashTables[1][table2HashIndex]){
                if(hashTables[0][table2HashIndex]==x){
                    hashTables[0][table2HashIndex] = 0;
                    break;
                }
            }

            table1HashIndex = (long)(table1HashIndex + pow((counter+1),2)) % tableSize; 
            table2HashIndex = (long)(table2HashIndex + pow((counter+1),2)) % tableSize; 

            numOfCollisions++;
            counter++;
        }
    }

    void print(){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < tableSize;j++){
                cout << "The table value at i = " << i << " and j = " << j << " is: " << hashTables[i][j] << endl;
            }
        }
    }
};