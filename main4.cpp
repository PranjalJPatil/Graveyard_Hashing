
#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <string>
#include "graveyardhashing_AT.cpp"
#include "robinhood.cpp"
#include "robinhood_TOMB.cpp"

using namespace std::chrono;
using namespace std;


double elapsed(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2) {
	return (duration_cast<duration<double>>(t2 - t1)).count();
}

int main(){
    int i =0 ;
    high_resolution_clock::time_point t1, t2;

    t1 = high_resolution_clock::now();

    while(i<100000000){
        if(1){
            
        }
        i++;;
    }
    t2 = high_resolution_clock::now();
	std::cout << "Time insert 100000 items : " + std::to_string(elapsed(t1, t2)) + " secs\n";

    i=0;
    int j=0;
    int temp =9, temp2;;
        t1 = high_resolution_clock::now();

    while(i<100000000){
        int x=temp;
        temp = j+1; ;
        temp2= x;
        i++;
    }
        t2 = high_resolution_clock::now();

	std::cout << "Time insert 100000 items : " + std::to_string(elapsed(t1, t2)) + " secs\n";

}