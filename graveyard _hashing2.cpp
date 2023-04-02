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
        n= 100;
        st = 0 ;
        keys.resize(n);
        values.resize(n);
    }
    bool query_(uint64_t x){
        
    }
    bool insert_(uint64_t x, int id){
        umap[x]= id;
       uint64_t hashval = id; //MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
      // cout<<"hashval"<<hashval<<endl;
       int ind;
       bool b=0;
       if(st > hashval ){
            int j = st;
            int ind;
            bool b=0;
            while(j != n){
                uint64_t temp  = umap[keys[j]];//MurmurHash64A(&keys[j], sizeof(uint64_t), 0);
                if(keys[j] == 0 && keys[j]==UINT64_MAX){
                    
                    if(b == 1){
                        for(int k= j ; k> ind;k-- ){
                            keys[k]= keys[k-1];
                        }
                        keys[ind] = x;
                        return ind;
                    }
                    if(keys[j] == 0){
                        keys[j] = x;
                        return j;
                    }
                    int k = j;
                    while(k!=n){
                        uint64_t temp  = umap[keys[k]];//MurmurHash64A(&keys[k], sizeof(uint64_t), 0);
                        if(temp > hashval){
                            break;
                        }
                        k++;
                    } 
                    if(k == n){
                        int p= 0;
                        while(p!=st){
                            uint64_t temp  = umap[keys[p]];//MurmurHash64A(&keys[p], sizeof(uint64_t), 0);
                            if(temp > hashval){
                                break;
                            }
                            p++;
                        }
                        if(p == st){
                            p--;
                            for(int l =j  ; l<p;l++){
                                l= l%n;
                                keys[l] = keys[(l+1)%n];
                            }
                            keys[p] = x;
                            return p ;
                        }
                        else{
                            p--;
                            for(int l =j  ; l<p;l++){
                                l= l%n;
                                keys[l] = keys[(l+1)%n];
                            }
                            keys[p] = x;
                            return p ;
                        }
                    }
                    else{
                        k--;
                        for(int p =j ; p< k;p++){
                            keys[p] = keys[p+1];
                        }
                        keys[k] = x;
                        return k;
                    }
                    break;
                }
                else if(b==0 && hashval < temp){
                    ind = j;
                    b=1;
                    j++;
                }
                else{
                    j++;
                }   
            }
            j = 0;
            if(b==0){
                while(j!=st){
                    uint64_t temp  = umap[keys[j]];//MurmurHash64A(&keys[j], sizeof(uint64_t), 0);
                    if(keys[j] == 0 && keys[j]==UINT64_MAX){
                        
                        if(b == 1){
                            for(int k= j ; k> ind;k-- ){
                                keys[k]= keys[k-1];
                            }
                            keys[ind] = x;
                            return ind;
                        }
                        if(keys[j] == 0){
                            keys[j] = x;
                            return j;
                        }
                        int k = j;
                        while(k!=st){
                            uint64_t temp  = umap[keys[k]];//MurmurHash64A(&keys[k], sizeof(uint64_t), 0);
                            if(temp > hashval){
                                break;
                            }
                            k++;
                        } 
                        if(k == n){

                        }
                        else{
                            k--;
                            for(int p =j ; p< k;p++){
                                keys[p] = keys[p+1];
                            }
                            keys[k] = x;
                            return k;
                        }
                        break;
                    }
                    else if(b==0 && hashval < temp){
                        ind = j;
                        b=1;
                        j++;
                    }
                    else{
                        j++;
                    }
                }
            }
            else{
                int j = 0;
                while(j!=st){
                    if(keys[j] == 0 ||keys[j]==UINT64_MAX){
                        
                        for(int p = j;p!=ind;p--){
                            if(p==0){
                                keys[p]= keys[n-1];
                            }
                            else{
                                keys[p]= keys[p-1];
                            }
                        }
                        keys[ind]= x;
                        return ind;
                    }
                    j++;
                }   
            }
       }
       else{
            // find free slot between hashval st
            // if yes b==1 shift and add
            //else back shift till found and add
            // if no  then find free slot and shit start b==1 shift and add
            // else put it at end
            int j = hashval;
            int ind;
            bool b=0;
            do {
                uint64_t temp  =   umap[keys[j]]; //MurmurHash64A(&keys[j], sizeof(uint64_t), 0);

                if(keys[j] == 0 || keys[j]==UINT64_MAX){
                    if(keys[j] == 0){
                        keys[j] = x;
                        return j;
                    }
                    if(j >= st && j<hashval){
                        for(int k=j;k>st;k--){
                            keys[k]= keys[k-1];
                            
                        }
                        st= st+1;
                        if(b==1){
                            for(int k=st-1;k>ind;k= (k-1)%n){
                                keys[k]= keys[(k-1)%n];
                            }
                            keys[ind]= x;
                            return ind;
                        }
                        else{
                            keys[st-1]= x;
                            return st-1;
                        }
                    }
                    else{
                        if(b == 1){
                            for(int k = j; k>ind;k= (k-1)%n){
                                keys[k]= keys[(k-1)%n];
                            }
                            keys[ind] = x;
                            return ind;
                        }
                        else{
                            int k;
                            for( k= j;j<st;k++){
                                uint64_t temp2  =umap[keys[k]];// MurmurHash64A(&keys[k], sizeof(uint64_t), 0);
                                if(temp2 > hashval){break;}
                            }
                            k--;
                            for(int p=ind;p<k;p= (p+1)%n){
                                keys[p]= keys[(p+1)%n];

                            }
                            keys[k]= x;
                            return k;
                        }
                    }
                }
                if(temp <= hashval){
                    
                }
                else if(b==0 && temp> hashval && ((j>=hashval && j<n) || (j<st &&j>=0) )){
                    ind= j;
                    b=1;
                }
                j++;
                j= j%n;
            }while(j!=hashval);


       }
       return UINT64_MAX;
    }
    void delete_(uint64_t x){
        
    }
    void print(){
        cout<<tot<<" total "<<endl;
        for(int i=0;i<100;i++){
            cout<<i<<"==="<<keys[i]<<"   ";
        }
    }
    void print2(){
        cout<<st<<" total "<<endl;
        for(int i=0;i<100;i++){
            if(keys[i]==0)continue;
            cout<<MurmurHash64A(&keys[i],sizeof(uint64_t),0)%n<<"        ";
        }
    } 
};