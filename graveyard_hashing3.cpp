#include<iostream>
#include<vector>
#include "hashutil.c"
#include<unordered_map>

using namespace std;

class Graveyard_Hash{
    vector<uint64_t> keys ;
    vector<uint64_t> values;
    uint64_t st;
    unordered_map<int,int> umap;
    int tot=0;
    size_t  n;
    int k =0 ;
    //tombstones are uint64_max;
    public:
    Graveyard_Hash(){
        n= 60;
        st = 0 ;
        keys.resize(n);
        values.resize(n);
    }
    bool query_(uint64_t x){
        
    }
    void insert_(uint64_t x){
        //umap[x]= id;
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
        int ind;
        bool b=0;
        if(hashval>= st){
            int i=hashval;
            do{
                int temp = MurmurHash64A(&keys[i], sizeof(uint64_t), 0)%n;
                if(keys[i] == 0 || keys[i]==UINT64_MAX){
                    if(keys[i] == 0){
                        if(b){
                            for(int k= i;k>ind;k=(k==0?n-1:k-1) ){
                                keys[k] =keys[k-1];
                            }
                            keys[ind] =x;
                            return ; 
                        }
                        else{
                            keys[i]= x;
                            return ;
                        }
                    }
                    else{
                        if(b){
                            for(int k= i;k>ind;k=(k==0?n-1:k-1) ){
                                 keys[k] =keys[k-1];
                            }
                            keys[ind] =x;
                            return ; 
                        }
                        else{
                            int j= i;
                            while(j!=st){
                                int temp2= MurmurHash64A(&keys[j], sizeof(uint64_t), 0)%n;
                                if(b==0 && temp > hashval){
                                    
                                    break;
                                }
                                j++;
                                j= j%n;
                            }
                            
                                if(j==0)
                                    j=n-1;
                                else
                                    j--;

                                for(int k = i;k!= j;k++ ){
                                    k= k%n;
                                    keys[k]= keys[(k+1)%n];
                                }
                                keys[j]=x;
                                return ;
                            
                        }
                    }
                }
                else if(b==0 && temp >  hashval ){
                    ind= i;
                    b=1;
                }
                else{
                }
                i++;
                i= i%n;
            }while(i!= st);

            for(int i=st;i!=hashval;i++){
                i= i%n;
                if(keys[i]== 0 || keys[i]==UINT64_MAX){
                    int k=i;
                    while(k>st){
                        int t= (k==0 ? n-1:k-1);
                        keys[k]= keys[t];
                        if(k==0)
                            k=n-1;
                        else k--;
                    }
                    break;
                }
            }
            st= st+1;
            st= st%n;
            if(b){
                int k= (st==0)?n-1:st-1;
                while(k!=ind){
                    int t= (k==0 ? n-1:k-1);
                    keys[k]=  keys[t];
                    if (k==0)k=n-1;
                    else
                    k--;
                }
                keys[ind]= x;
                return ;
            }
            else{
                keys[st-1] = x;
                return;
            }
            cout<<"No FREE SLOTS";
        }
        else{
            int i= st;
            do{
                int t2= MurmurHash64A(&keys[i], sizeof(uint64_t), 0)%n;; 
                if(keys[i] == 0|| keys[i]==UINT64_MAX){
                    if(keys[i]==0){
                        if(b){
                            for(int k= i;k>ind;k= (k==0?n-1:k-1)){
                                int tp= (k==0)?n-1:k-1;
                                keys[k]= keys[tp];
                            }
                            keys[ind]= x;
                            return ;
                        }
                        else{
                            keys[i]= x;
                            return ;
                        }
                    }
                    else{
                        if(b){
                            for(int k= i;k>ind;k= (k==0?n-1:k-1)){
                                int tp= (k==0)?n-1:k-1;
                                keys[k]= keys[tp];
                            }
                            keys[ind]= x;
                            return ;
                        }
                        else{
                            int j= i;
                            while(j!=st){
                                int temp3= MurmurHash64A(&keys[j], sizeof(uint64_t), 0)%n;
                                if(keys[j] == 0 ||UINT64_MAX)continue;
                                if(temp3 > hashval ){
                                    break;
                                }
                                j++;
                                j= j%n;
                            }
                            if(j ==0){
                                j=n-1;
                            }
                            else j--;
                            for(int p= i;p!=j;p++){
                                p=p%n;
                                keys[p]= keys[(p+1)%n];
                            }
                            keys[i] = x;
                            return ;
                        }
                    }
                }
                else if( b==0 && t2 > hashval){
                    ind= i;
                    b=1;
                }
                i++;
                i= i%n;
            }while(i!=st);
        }
    }
    void print(){
        cout<<st<<" total "<<endl;
        for(int i=0;i<n;i++){
            cout<<i<<"==="<<keys[i]<<"   ";
        }
    }
    void print2(){
        cout<<st<<" total "<<endl;
        for(int i=0;i<n;i++){
            if(keys[i]==0)continue;
            cout<<MurmurHash64A(&keys[i], sizeof(uint64_t), 0)%n<<"        ";
        }
    } 
};