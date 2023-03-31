#include<iostream>
#include<vector>

#include "graveyard_hashing.cpp"

using namespace std;

int main(){

    Graveyard_Hash *ob = new Graveyard_Hash();
    uint64_t t= 4;
    for(uint64_t i=1;i<=100;i++)
    {    ob->insert_(i);
        ob->print();
    }
    for(uint64_t i=1;i<=100;i++)
        cout<<" "<<i<<" "<<ob->query_(i)<<endl;
    return 1;

}