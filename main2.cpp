#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <string>
#include "graveyardhashing_AT.cpp"
#include "robinhood.cpp"
#include "robinhood_TOMB.cpp"



int main(){
    Graveyard_Hash *ob = new Graveyard_Hash(1000);
    for(int i=1;i<=900;i++){
        ob->insert_(i);
    }
    int st= 901;
    int del= 1;
    for(int i=0;i<100;i++){
        for(int j=del;j<del+50;j++){
            ob->delete_(j);
        }
        del= del+50;
        for(int j=st;j<st+50;j++){
            if(j==1869){
                ob->insert_(j);
            }else
            ob->insert_(j);
        }
        for(int j=st;j<st+50;j++){
            if(ob->query_(j)){

            }else cout<<j<<"wrong"<<endl;
        }
        st= st+50;

    }

}