#include<iostream>
#include<vector>
#include "hashutil.c"

using namespace std;

class Graveyard_Hash{
    vector<uint64_t> keys ;
    vector<uint64_t> values;
    int tot=0;
    size_t  n;
    int k =0 ;
    //tombstones are uint64_max;
    public:
    Graveyard_Hash(){
        n= 100;
        keys.resize(n);
        values.resize(n);
    }
    bool query_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x,sizeof(uint64_t),0) % n;
        uint64_t i = hashval;
        int k=0;
        do{
            if(keys[i] == 0 || ((MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) > hashval && (MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) <= i )){
                return 0;
            }   
            else if(keys[i] == x){
              //  cout<<k<<" ";
                return 1;
            }        
            i++;
            i = i%n;
            k++;
        }while(i != hashval);
        cout<<k<<" ";
        return 0;
    }
    void insert_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x,sizeof(uint64_t),0) % n;
        uint64_t i = hashval;
        bool b = 0, flag=0;;
        uint64_t ind= 0;
        int k =0;
        cout<<"popoplpoplp"<<endl;
    //  cout<<i<<" fffff "<<x<<endl;
       cout<<"popop";
        do{
            cout<<"y";
            if(keys[i] == 0  || keys[i] ==  UINT64_MAX){
              //  cout<<"hiij";
                if(!b){
                    if(keys[i] == UINT64_MAX){
                    int j = i;
                    do{
                        j++;
                        j= j%n;
                        if(keys[j]==UINT64_MAX){
                        }
                        else if(i <  hashval){
                        //    cout<<"ggggg";
                           if((MurmurHash64A(&keys[j], sizeof(uint64_t),0)%n) > i){
                            if((MurmurHash64A(&keys[j], sizeof(uint64_t),0)%n) > hashval){
                                break;
                            }
                           }
                           else{
                                break;
                           }
                        }
                        else {
                         //   cout<<i<<" "<<j<<" "<<(MurmurHash64A(&keys[j], sizeof(uint64_t),0)%n > hashval)<<" dedede"<<(MurmurHash64A(&keys[j], sizeof(uint64_t),0)%n )<<"edkje";
                            if(MurmurHash64A(&keys[j], sizeof(uint64_t),0)%n > hashval && MurmurHash64A(&keys[j], sizeof(uint64_t),0)%n <= j){
                           //     cout<<"oekdoekeo";
                                break;
                            }
                        }
                    }while( j!=hashval);
                    if(j==0)j=n-1;
                    else j--;
                   // cout<<"  i  "<<i<<"  j  "<<j<<endl;
                    while(i!=j){
                        keys[i] =  keys[(i+1)%n];
                        i= (i+1)%n;
                    }
                    keys[j]= x;
                    return ;
                    }
                    k++;
                    tot+=k;
                    keys[i] = x;
                    return ;
                }
                else{
                    uint64_t temp = keys[ind];

                    for(int j=ind ;  j != i ; j++){
                        j = j%n;
                        uint64_t temp2 = keys[(j+1)%n];
                        keys[(j+1)%n] = temp;
                        temp = temp2;;
                        
                    }
                    keys[ind] = x;
                    return;
                }
            }   
            else if(b==0 && ((MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) > i) && i < hashval  ){
                if(hashval < (MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) ){
                    ind=i;
                    b=1;
                }
            }
            else if(b==0 && ((MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) > i) && i >= hashval){

            }
            else if(b==0 && ((MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) <= i) && i< hashval){
                ind = i;
                b=1;
            }
            else if(b==0 && (MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) > hashval ){
                ind= i;
                b=1;
            }
            i++;
            k++;
            if(i==n){
                i=0;
            }
        }while(i != hashval);
        return ;
    }
    void delete_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x,sizeof(uint64_t),0) % n;
        uint64_t i = hashval;
        int k=0;
        do{
            if(keys[i] == 0 || ((MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) > hashval && (MurmurHash64A(&keys[i],sizeof(uint64_t),0) % n) <= i )){
                return ;
            }   
            else if(keys[i] == x){
               // cout<<k<<" ";
                keys[i] = UINT64_MAX;
                return ;
            }        
            i++;
            i = i%n;
            k++;
        }while(i != hashval);
       // cout<<k<<" ";
        return ;
    }
    void print(){
        cout<<tot<<" total "<<endl;
        for(int i=0;i<100;i++){
            cout<<i << " == "<<keys[i]<<"        ";
        }
    }
    void print2(){
        cout<<tot<<" total "<<endl;
        for(int i=0;i<100;i++){
            cout<<MurmurHash64A(&keys[i],sizeof(uint64_t),0)%n<<"        ";
        }
    } 
};