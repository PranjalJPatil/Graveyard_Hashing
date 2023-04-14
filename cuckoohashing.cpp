#include "hashutil.h"
#include <iostream>
#include <vector>
#include <math.h>

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
    long hastTableSize;
    // long* hashTables2;

    CuckooHash(long size, long initTable1HashLength, long initTable2HashLength, long initTable1Seed, long initTable2Seed){
        hashTables = new long*[2];

        for(int i = 0; i < 2;i++){
            hashTables[i] = new long[size];
        }

        tableSize = size;
        // table1HashLength = initTable1HashLength;
        table1Seed = initTable1Seed;
        // table2HashLength = initTable2HashLength;
        table2Seed = initTable2Seed;
    }

    void insert(long x, long numOfMaxLoop){
        bool foundItem = false;

        // while(!foundItem){

        // }

        if(lookup(x)){
            return;
        }

        long insert_val = x;

        long table1HashIndex = MurmurHash64A(&x,tableSize,table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,tableSize,table2Seed) % tableSize;

        for(int i = 0; i < numOfMaxLoop;i++){
            if(!hashTables[0][table1HashIndex]){
                hashTables[0][table1HashIndex] = insert_val;
                return;
            }

            long oldItemInTable1 = hashTables[0][table1HashIndex];
            hashTables[0][table1HashIndex] = insert_val;
            insert_val = oldItemInTable1;



            if(!hashTables[1][table2HashIndex]){
                hashTables[1][table2HashIndex] = insert_val;
                return;
            }


            long oldItemInTable2 = hashTables[0][table2HashIndex];
            hashTables[0][table2HashIndex] = insert_val;
            insert_val = oldItemInTable2;

            //// Swapping
            rehash();
            // insert(x,numOfMaxLoop);
 
        }
    }

    void rehash(){
        table1Seed = pow(table1Seed,2);
        table2Seed = pow(table2Seed,2);
    }

    bool lookup(long x){
        long table1HashIndex = MurmurHash64A(&x,tableSize,table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,tableSize,table2Seed) % tableSize;

        return hashTables[0][table1HashIndex] == x || hashTables[1][table2HashIndex] == x;
    }
};