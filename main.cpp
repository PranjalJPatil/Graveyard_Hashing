#include<iostream>
#include<vector>

#include "graveyard_hashing.cpp"

using namespace std;

int main(){

    Graveyard_Hash *ob = new Graveyard_Hash();
    uint64_t t= 4;
    for(uint64_t i=1;i<=100;i++)
    {    ob->insert_(i);}
    ob->print2();
    for(uint64_t i=1;i<=100;i++)
        cout<<" "<<i<<" "<<ob->query_(i)<<endl;
    for(uint64_t i=1;i<=30;i++)
        ob->delete_(i);
            
    for(uint64_t i=1;i<=27;i++)
    {  
        ob->insert_(i);
        cout<<"insert="<<i<<endl;
        //ob->print2();
        //cout<<"q";
    }
    ob->insert_(30);
    ob->delete_(44);
    ob->insert_(29);
   // ob->print2();
    for(uint64_t i=1;i<=100;i++)
        cout<<" "<<i<<" "<<ob->query_(i)<<endl;
    return 1;

}