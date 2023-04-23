#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <string>
#include "graveyardhashing_AT.cpp"
#include "robinhood.cpp"
#include "robinhood_TOMB.cpp"



int main(){
    Graveyard_Hash *ob = new Graveyard_Hash(10000);

    for(int i=1;i<=9000;i++){
        ob->insert_(i);
    }
    int st= 9001;
    int del= 1;
    int tot=0;
    for(int i=0;i<3000;i++){
       // cout<<i<<" ";
       
        for(int j=del;j<del+50;j++){
            
            ob->delete_(j);
        }
       
        del= del+50;

        for(int j=st;j<st+50;j++){
            if(j==239){
               // ob->print();
                ob->insert_(j);
                //ob->print();
            }else
            tot+=ob->insert_(j);
            
            if(ob->ccc()){
                cout<<endl<<"element asing problem"<<j<<" "<<ob->printhv(j)<<endl;
            }

        }
      
        for(int j=del;j<st+50;j++){
            if(ob->query_(j)){
            }else 
                cout<<j<<" "<<ob->printhv(j)<<"wrong"<<endl;
        }
        st= st+50;
        //cout<<endl;
        //ob->print();
        //cout<<endl;
       // ob->resize_();
    }
    cout<<tot;

}