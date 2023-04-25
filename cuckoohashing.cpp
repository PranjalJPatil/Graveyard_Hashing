#include "hashutil.c"
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;


//// Modification Made


/* 
 Struct for hashing with Cuckoo Hashing
 */
struct CuckooHash{
    long** hashTables;          //// Pointer of points in representation of 2D array
    long tableSize;             //// Table Size
    long table1HashLength;
    long table2HashLength;
    long table1Seed;            //// Table 1 Seed
    long table2Seed;            //// Table 2 Seed
    long baseSize;              
    long totalCapacity;         
    long numberOfElements;      //// Number of Elements
    double resizeFactor;
    double loadFactor;
    long maxNumCollisions;     
    long maxNumIterations;      //// Maximum Number of iterations allowed within the hash table.

    //// Initializing the CuckooHash class
    CuckooHash(long initSize, long initMaxNumIterations, double initResizeFactor, double initLoadFactor, long initTable1HashLength, long initTable2HashLength, long initTable1Seed, long initTable2Seed){
        hashTables = new long*[2];

        //// Initializing the hash tables
        for(int i = 0; i < 2;i++){
            hashTables[i] = (long*)malloc(sizeof(long)*initSize);
        }

        numberOfElements = 0;                //// Number of Elements
        loadFactor = initLoadFactor;        
        tableSize = initSize;                //// Table size of Computer Science
        totalCapacity = tableSize * 2;      
        baseSize = tableSize;
        resizeFactor = initResizeFactor;

        //// Number of table 
        maxNumCollisions = initMaxNumIterations;
        maxNumIterations = initMaxNumIterations;

        table1Seed = initTable1Seed;
        table2Seed = initTable2Seed;
    }

    //// Insert item x into the hash table.
    void insert(long x){
        bool foundItem = false;

        //// If the value already exists, return immediately
        if(lookup(x)){
            return;
        }

        long insert_val = x;

        long table1HashIndex = MurmurHash64A(&x,sizeof(long),table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,sizeof(long),table2Seed) % tableSize;
        long numOfCollisions = 0;
        long numOfIterations = 0;
        long counter = 0;

        //// If the collision exists and the number of iterations is well below the limit, keep looping
        while(numOfIterations <= maxNumIterations){

            //// If the hash table at the first row is empty, insert an item.
            if(!hashTables[0][table1HashIndex]){
                hashTables[0][table1HashIndex] = insert_val;
                numberOfElements++;
                break;
            }
            
            //// If the hash table at the first row is non-empty, swap items.
            long hashTable1Item = hashTables[0][table1HashIndex];
            hashTables[0][table1HashIndex] = insert_val;
            insert_val = hashTable1Item;

            //// If the hash table at the second row is empty, insert an item.
            if(!hashTables[1][table2HashIndex]){
                hashTables[0][table2HashIndex] = insert_val;
                numberOfElements++;
                break;
            }

            //// If the hash table at the second row is non-empty, swap items.
            long hashTable2Item = hashTables[0][table2HashIndex];
            hashTables[0][table2HashIndex] = insert_val;
            insert_val = hashTable2Item;


            long nextTable1HashPos = (long)(table1HashIndex + pow((counter+1),2));
            long nextTable2HashPos = (long)(table1HashIndex + pow((counter+1),2));

            //// If the nextIndex for both hash tables exceed the size of table, increase the number of iterations.
            if(nextTable1HashPos >= tableSize && nextTable2HashPos >= tableSize){
                numOfIterations++;
            }

            //// Obtain the table1HashIndex and table2HashIndex
            table1HashIndex = (long)(nextTable1HashPos % baseSize); 
            table2HashIndex = (long)(nextTable2HashPos % baseSize); 

            counter++;
            numOfCollisions++;
        }
    }

    //// Look up the items
    bool lookup(long x){
        long insert_val = x;

        long numOfCollisions = 0;
        long numOfIterations = 0;

        long table1HashIndex = MurmurHash64A(&x,sizeof(long),table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,sizeof(long),table2Seed) % tableSize;
        long counter = 0;

        //// If the collision exists and the number of iterations is well below the limit, keep looping
        while(numOfIterations < maxNumIterations){
            //// If the element exists at first row of hash table, return true
            if(hashTables[0][table1HashIndex]){
                if(hashTables[0][table1HashIndex]==x){
                    return true;
                }
            }
            
            //// If the element exists at second row of hash table, return true
            if(hashTables[1][table2HashIndex]){
                if(hashTables[0][table2HashIndex]==x){
                    return true;
                }
            }

            long nextTable1HashPos = (long)(table1HashIndex + pow((counter+1),2));
            long nextTable2HashPos = (long)(table1HashIndex + pow((counter+1),2));

            //// If the nextIndex for both hash tables exceed the size of table, increase the number of iterations.
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

    //// Delete item x at hash table 
    void deleteItem(long x){
        long numOfCollisions = 0;
        long numOfIterations = 0;

        long table1HashIndex = MurmurHash64A(&x,sizeof(long),table1Seed) % tableSize;
        long table2HashIndex = MurmurHash64A(&x,sizeof(long),table2Seed) % tableSize;

        long counter = 0;

        //// If the the number of iterations is well below the limit, keep looping
        while(numOfIterations < maxNumIterations){

            //// If the item exists at either hash table, delete items.
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

    //// Print the hash tables.
    void print(){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < tableSize;j++){
                cout << "The table value at i = " << i << " and j = " << j << " is: " << hashTables[i][j] << endl;
            }
        }
    }

    //// Return the number of elements.
    long numOfElements(){
        return numberOfElements;
    }
};