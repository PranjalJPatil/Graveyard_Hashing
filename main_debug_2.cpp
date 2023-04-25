#include "cuckoohashing.cpp"

//// Debug code for cuckoo hashing probing.
int main(){

    
    long size = 10;
    double loadFactor = 0.5;
    double enLargeFactor = 2.0;
    long seed = 0;
    long maxIterations = 10;
    long table1Seed = 30;
    long table2Seed = 40;

    CuckooHash ch(size, maxIterations,enLargeFactor, loadFactor, size, size, table1Seed, table2Seed);

    ch.insert(5);
    ch.insert(10);
    ch.insert(20);

    ch.print();

    bool result = ch.lookup(5);
    cout << "The result is: " <<  result << endl;

    return 0;
}