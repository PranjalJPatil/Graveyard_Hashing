#include<iostream>
#include<vector>
#include "hashutil.c"

using namespace std;

class Graveyard_Hash{
    vector<uint64_t> v ;
    int tot=0;
    size_t  n;
    //tombstones are uint64_max;
    public:
    Graveyard_Hash(){
        n= 100;
        v.resize(n);
       // b.resize(n);
    }
    bool query_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x,sizeof(uint64_t),0) % n;
        uint64_t i = hashval;
        int k=0;
        do{
            if(v[i] == 0 || ((MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) > hashval && (MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) <= i )){
                return 0;
            }   
            else if(v[i] == x){
                cout<<k<<" ";
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
        
        cout<<i<<" fffff "<<x<<endl;
        do{
            if(v[i] == 0  || v[i] ==  UINT64_MAX){
                if(!b){
                    v[i] = x;
                    return ;
                }
                else{
                    uint64_t temp = v[ind];

                    for(int j=ind ;  j != i ; j++){
                        j = j%n;
                        uint64_t temp2 = v[(j+1)%n];
                        v[(j+1)%n] = temp;
                        temp = temp2;;
                        
                    }
                    v[ind] = x;
                    return;
                }
            }   
            else if(b==0 && ((MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) > i) && i< hashval ){
                if(hashval < (MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) ){
                    ind=i;
                    b=1;
                }
            }
            else if(b==0 && ((MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) <= i) && i< hashval){
                ind = i;
                b=1;
            }
            else if(b==0 && (MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) > hashval ){
                ind= i;
                b=1;
            }
            i++;
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
            if(v[i] == 0 || ((MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) > hashval && (MurmurHash64A(&v[i],sizeof(uint64_t),0) % n) <= i )){
                return ;
            }   
            else if(v[i] == x){
                cout<<k<<" ";
                v[i] = UINT64_MAX;
                return ;
            }        
            i++;
            i = i%n;
            k++;
        }while(i != hashval);
        cout<<k<<" ";
        return ;
    }
    void print(){
        for(int i=0;i<100;i++){
            cout<<i << " == "<<v[i]<<"        ";
        }
    }
};