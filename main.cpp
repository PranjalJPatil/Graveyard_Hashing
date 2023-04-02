#include<iostream>
#include<vector>

#include "graveyard_hashing3.cpp"

using namespace std;

int main(){

    Graveyard_Hash *ob = new Graveyard_Hash();
    uint64_t t= 4;
    
    for(int i=1;i<=60;i++){
        ob->insert_(i);
    }

     ob->print();
   // ob->insert_(3, 0);
     ob->print2();
    //ob->insert_(4, 1);
    // ob->print();
   // ob->inse
    ob->print();
        
    return 1;

}