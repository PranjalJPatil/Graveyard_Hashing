#include "quadratic.cpp"

int main(){

    long size = 10;
    double loadFactor = 0.5;
    double enLargeFactor = 2.0;
    long seed = 20;
    long maxIterations = 4;
    QuadraticHash qh(size,loadFactor, enLargeFactor,seed,maxIterations);

    qh.insert(5);
    qh.insert(10);
    qh.insert(20);
    qh.insert(40);
    qh.insert(50);
    qh.insert(80);
    qh.insert(100);
    // qh.insert(10);
    bool result = qh.lookup(5);

    cout << "The result is: " << result << endl;

    result = qh.lookup(8);
    cout << "The result is: " << result << endl;

    result = qh.lookup(5);
    result = qh.lookup(20);
    cout << "The result is: " << result << endl;

    result = qh.lookup(40);
    cout << "The result is: " << result << endl;

    result = qh.lookup(50);
    cout << "The result is: " << result << endl;

    result = qh.lookup(80);
    cout << "The result is: " << result << endl;

    result = qh.lookup(100);
    cout << "The result is: " << result << endl;


    qh.deleteItem(5);
    qh.print();


    return 0;
}