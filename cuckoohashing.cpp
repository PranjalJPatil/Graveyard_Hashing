#include "hashutil.c"
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;


//// Modification Made

//// Hashing
struct CuckooHash{
    // vector<int> newElements;
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
    long maxNumIterations;

    CuckooHash(long initSize, long initMaxNumIterations, double initResizeFactor, double initLoadFactor, long initTable1HashLength, long initTable2HashLength, long initTable1Seed, long initTable2Seed){
        hashTables = new long*[2];

        for(int i = 0; i < 2;i++){
            hashTables[i] = (long*)malloc(sizeof(long)*initSize);
        }

        numberOfElements = 0;
        loadFactor = initLoadFactor;
        tableSize = initSize;
        totalCapacity = tableSize * 2;
        baseSize = tableSize;
        resizeFactor = initResizeFactor;
        maxNumCollisions = initMaxNumIterations;
        maxNumIterations = initMaxNumIterations;

        table1Seed = initTable1Seed;
        table2Seed = initTable2Seed;
    }

    void insert(long x){
        bool foundItem = false;

        if(lookup(x)){
            return;
        }

        long insert_val = x;

        long table1HashIndex = MurmurHash64A(&x,sizeof(long),table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,sizeof(long),table2Seed) % tableSize;

        cout << "The table1HashIndex is: " << table1HashIndex << endl;
        cout << "The table2HashIndex is: " << table2HashIndex << endl;

        long numOfCollisions = 0;
        long numOfIterations = 0;
        long counter = 0;

        while(numOfIterations <= maxNumIterations){
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

            long nextTable1HashPos = (long)(table1HashIndex + pow((counter+1),2));
            long nextTable2HashPos = (long)(table1HashIndex + pow((counter+1),2));

            if(nextTable1HashPos >= tableSize && nextTable2HashPos >= tableSize){
                numOfIterations++;
            }

            table1HashIndex = (long)(nextTable1HashPos % baseSize); 
            table2HashIndex = (long)(nextTable2HashPos % baseSize); 

            counter++;
            numOfCollisions++;

            // if(maxNumCollisions < numOfCollisions){
            //     maxNumCollisions = numOfCollisions;
            // }
        }
    }

    bool lookup(long x){
        long insert_val = x;

        long numOfCollisions = 0;
        long numOfIterations = 0;

        long table1HashIndex = MurmurHash64A(&x,sizeof(long),table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,sizeof(long),table2Seed) % tableSize;

        cout << "Lookup: The index of item " << x << " at hash table 1 is: " << table1HashIndex << endl;
        cout << "Lookup: The index of item " << x << " at hash table 2 is: " << table2HashIndex << endl;

        long counter = 0;

        while(numOfIterations < maxNumIterations){
            if(hashTables[0][table1HashIndex]){
                if(hashTables[0][table1HashIndex]==x){
                    return true;
                }
            }
            
            if(hashTables[1][table2HashIndex]){
                if(hashTables[0][table2HashIndex]==x){
                    return true;
                }
            }


            long nextTable1HashPos = (long)(table1HashIndex + pow((counter+1),2));
            long nextTable2HashPos = (long)(table1HashIndex + pow((counter+1),2));

            if(nextTable1HashPos >= tableSize && nextTable2HashPos >= tableSize){
                numOfIterations++;
            }

            table1HashIndex = (long)(nextTable1HashPos % baseSize); 
            table2HashIndex = (long)(nextTable2HashPos % baseSize); 

            numOfCollisions++;
            counter++;
        }

        return false;
    }

    // void resize(){
    //     long newSize = tableSize * resizeFactor;
    //     long** newHashTables = new long*[2];

    //     for(int i = 0; i < 2;i++){
    //         newHashTables[i] = new long[newSize];
    //     }
        
    //     for(int i = 0; i < 2;i++){
    //         for(int j = 0; j < tableSize;j++){
    //             if(hashTables[i][j]){
    //                 newHashTables[i][j] = hashTables[i][j];
    //             }
    //         }
    //     }

    //     tableSize = newSize;
    //     delete[] hashTables;
    //     hashTables = newHashTables;
    //     totalCapacity = tableSize * 2;
    // }

    void deleteItem(long x){
        long numOfCollisions = 0;
        long numOfIterations = 0;

        long table1HashIndex = MurmurHash64A(&x,sizeof(long),table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,sizeof(long),table2Seed) % tableSize;

        long counter = 0;

        while(numOfIterations < maxNumIterations){
            if(hashTables[0][table1HashIndex]){
                if(hashTables[0][table1HashIndex]==x){
                    numberOfElements--;
                    hashTables[0][table1HashIndex] = 0;
                    break;
                }
            }
            
            if(hashTables[1][table2HashIndex]){
                if(hashTables[0][table2HashIndex]==x){
                    numberOfElements--;
                    hashTables[0][table2HashIndex] = 0;
                    break;
                }
            }

            long nextTable1HashPos = (long)(table1HashIndex + pow((counter+1),2));
            long nextTable2HashPos = (long)(table1HashIndex + pow((counter+1),2));

            if(nextTable1HashPos >= tableSize && nextTable2HashPos >= tableSize){
                numOfIterations++;
            }

            table1HashIndex = (long)(nextTable1HashPos % baseSize); 
            table2HashIndex = (long)(nextTable2HashPos % baseSize); 

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