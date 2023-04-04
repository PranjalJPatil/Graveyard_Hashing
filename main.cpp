#include<iostream>
#include<vector>

#include "graveyardhashing_AT.cpp"
#include "robinhood.cpp"
#include "robinhood_TOMB.cpp"


using namespace std;

int main(){

    Robinhood_Hash *ob = new Robinhood_Hash(100);
    for(int i=1;i<=100;i++){
        ob->insert_(i);
    }
    for(int i=1;i<=45;i++){
         cout<<i<<" "<<ob->query_(i)<<endl;
    }
    cout<<"ppppppppppppppppppppppp";
    for(int i=1;i<=15;i++){
         ob->delete_(i);
     }
    for(int i=1;i<=100;i++){
         cout<<i<<" "<<ob->query_(i)<<endl;
    }
    //ob->print();
    // for(int i=1;i<10000;i++){
    //     ob->insert_(i);
    // }
    // for(int i=1;i<10000;i++){
    //     bool b= ob->query_(i);
    //     if(b==0)cout<<i<<"WRONG ELEMENT-1";
    // }
    // for(int i=1;i<5000;i++){
    //     ob->delete_(i);  
    // }
    // for(int i=1;i<5000;i++){
    //     bool b= ob->query_(i);
    //     if(b==1)cout<<"WRONG ELEMENT-2";
    // }
    //  for(int i=5000;i<10000;i++){
    //     bool b= ob->query_(i);
    //     if(b==0)cout<<"WRONG ELEMENT-3";
    // }
    // for(int i=2001;i<5000;i++){
    //     ob->insert_(i);  
    // }
    // for(int i=1;i<=2000;i++){
    //     bool b= ob->query_(i);
    //     if(b==1)cout<<"WRONG ELEMENT-2";
    // }
    //  for(int i=2001;i<10000;i++){
    //     bool b= ob->query_(i);
    //     if(b==0)cout<<"WRONG ELEMENT-3";
    // }
    return 1;

}