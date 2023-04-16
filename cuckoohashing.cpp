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
    long hastTableSize;
    double loadFactor;
    // long* hashTables2;

    CuckooHash(long size, double initLoadFactor, long initTable1HashLength, long initTable2HashLength, long initTable1Seed, long initTable2Seed){
        hashTables = new long*[2];

        for(int i = 0; i < 2;i++){
            hashTables[i] = new long[size];
        }

        loadFactor = initLoadFactor;
        tableSize = size;
        // table1HashLength = initTable1HashLength;
        table1Seed = initTable1Seed;
        // table2HashLength = initTable2HashLength;
        table2Seed = initTable2Seed;
    }

    void insert(long x, long numOfMaxLoop){
        if(tableSize >= tableSize * loadFactor){
            long factor = 2;
            resize(factor);
        }

        bool foundItem = false;

        // while(!foundItem){

        // }

        if(lookup(x)){
            return;
        }

        long insert_val = x;

        // long table1HashIndex = MurmurHash64A(&x,tableSize,table1Seed) % tableSize;
        // long table2HashIndex = MurmurHash64A(&x,tableSize,table2Seed) % tableSize;

        for(int i = 0; i < numOfMaxLoop;i++){

            long table1HashIndex = MurmurHash64A(&x,tableSize,table1Seed) % tableSize;
            long table2HashIndex = MurmurHash64A(&x,tableSize,table2Seed) % tableSize;

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

    void resize(long factor){
        long newSize = tableSize * factor;
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

    }

    void deleteItem(long x, long numOfMaxLoop){

        long delete_val = x;


        for(int i = 0; i < numOfMaxLoop;i++){

               for(int i = 0; i < numOfMaxLoop;i++){
                    long table1HashIndex = MurmurHash64A(&x,tableSize,table1Seed) % tableSize;
                    long table2HashIndex = MurmurHash64A(&x,tableSize,table2Seed) % tableSize;

                    if(hashTables[0][table1HashIndex]){
                        hashTables[0][table1HashIndex] = NULL;
                        return;
                    }

                    long oldItemInTable1 = hashTables[0][table1HashIndex];
                    hashTables[0][table1HashIndex] = delete_val;
                    delete_val = oldItemInTable1;



                    if(hashTables[1][table2HashIndex]){
                        hashTables[1][table2HashIndex] = NULL;
                        return;
                    }


                    long oldItemInTable2 = hashTables[0][table2HashIndex];
                    hashTables[0][table2HashIndex] = delete_val;
                    delete_val = oldItemInTable2;

                    //// Swapping
                    rehash();
                    // insert(x,numOfMaxLoop);
        }
               

        }
    }
};