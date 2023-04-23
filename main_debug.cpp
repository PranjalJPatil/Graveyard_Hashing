#include "quadratic.cpp"
// #include "cuckoohashing.cpp"

int main(){

    long size = 50;
    double loadFactor = 0.5;
    double enLargeFactor = 2.0;
    long seed = 0;
    long maxIterations = 3;
    QuadraticHash qh(size,loadFactor, enLargeFactor,seed,maxIterations);

    qh.insert(5);
    // qh.insert((long)5);
    qh.insert(10);
    qh.insert(20);
    qh.insert(40);
    qh.insert(50);
    // qh.insert(80);
    // qh.insert(100);
    // qh.insert(10);
    // qh.print();

    bool result = qh.lookup((long)5);
    cout << "The result is: " << result << endl;
    // result = qh.lookup(8);
    // cout << "The result is: " << result << endl;
    // result = qh.lookup(5);
    result = qh.lookup(20);
    cout << "The result is: " << result << endl;
    // result = qh.lookup(40);
    // cout << "The result is: " << result << endl;
    // result = qh.lookup(50);
    // cout << "The result is: " << result << endl;
    // result = qh.lookup(80);
    // cout << "The result is: " << result << endl;
    // result = qh.lookup(100);
    // cout << "The result is: " << result << endl;





    // qh.deleteItem(5);
    // qh.print();
    // long table1Seed = 30;
    // long table2Seed = 40;

    // CuckooHash ch(size, enLargeFactor, loadFactor, size, size, table1Seed, table2Seed);
    // ch.lookup(5);

    // ch.insert(5);
    // ch.insert(10);
    // ch.insert(20);










    return 0;
}