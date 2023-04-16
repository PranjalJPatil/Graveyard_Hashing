#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <string>
#include "graveyardhashing_AT.cpp"
#include "robinhood.cpp"
#include "robinhood_TOMB.cpp"



int main(){
    Robinhoodtomb_Hash *ob = new Robinhoodtomb_Hash(10000);
    
    

    for(int i=1;i<=9000;i++){
        ob->insert_(i);
    }
    int st= 9001;
    int del= 1;
    for(int i=0;i<100;i++){
        cout<<i<<" ";
       
        for(int j=del;j<del+500;j++){
            
            ob->delete_(j);
        }
       
        del= del+500;

        for(int j=st;j<st+500;j++){
            ob->insert_(j);
        }
      
        for(int j=del;j<st+500;j++){
            if(ob->query_(j)){
            }else cout<<j<<"wrong"<<endl;
        }
        st= st+500;
   
        ob->resize_();
        
       //ob->print();

    }

}