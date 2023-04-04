#include<iostream>
#include<vector>
#include "hashutil.h"
#include<unordered_map>

using namespace std;

class Robinhoodtomb_Hash{
    vector<uint64_t> keys ;
    vector<uint64_t> values;
    uint64_t st;
    int tot=0;
    size_t  n;
    int k =0 ;
    //tombstones are uint64_max;
    public:
    Robinhoodtomb_Hash(size_t tn){
        n= tn;
        st = 0 ;
        keys.resize(n);
        values.resize(n);
    }
    bool query_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
        int i;
        if(hashval < st){
            i = st; 
        }
        else
            i= hashval;
        do{
            int temp =  MurmurHash64A(&keys[i], sizeof(uint64_t), 0)%n;
            if(keys[i] == x)return 1;
            else if(keys[i] == 0 ){return 0;
            }
            else if(keys[i] == UINT64_MAX){
                i++;
                i= i%n;
            }
            else if(temp > hashval ){
                return 0;
            }
            else{
                i++;
                i= i%n;
            }
        }while(i!=st);
        return 0;

    }
    void insert_(uint64_t x){
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
                            do{
                                int temp2= MurmurHash64A(&keys[j], sizeof(uint64_t), 0)%n;
                                if(keys[j]==UINT64_MAX){j++;j=j%n;continue;}
                                else if(keys[j]== 0){break;}
                                else if(b==0 && temp2 > hashval){
                                    
                                    break;
                                }
                                j++;
                                j= j%n;
                            }while(j!=st);
                            
                                if(j==0)
                                    j=n-1;
                                else
                                    j--;

                                for(int k = i;k!= j;k=(k+1)%n ){
                                  //  k= k%n;
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
                            do{
                                int temp3= MurmurHash64A(&keys[j], sizeof(uint64_t), 0)%n;
                                if(keys[j] == 0 ||keys[j]==UINT64_MAX){
                                    j++;
                                    j= j%n;
                                    continue;}
                                if(temp3 > hashval ){
                                    break;
                                }
                                j++;
                                j= j%n;
                            }while(j!=st);
                            if(j ==0){
                                j=n-1;
                            }
                            else j--;
                            for(int p= i;p!=j;p++){
                                p=p%n;
                                keys[p]= keys[(p+1)%n];
                            }
                            keys[j] = x;
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

    void delete_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
     //   cout<<st<<" "<<hashval<<endl;
        int i;
        if(hashval < st){
            i = st; 
        }
        else
            i= hashval;
        do{
            int temp =  MurmurHash64A(&keys[i], sizeof(uint64_t), 0)%n;
            if(keys[i] == x){keys[i]=UINT64_MAX;return ;}
            else if(keys[i] == 0 ){return ;
            }
            else if(keys[i] == UINT64_MAX){
                i++;
                i= i%n;
            }
            else if(temp > hashval ){
                return ;
            }
            else{
                i++;
                i= i%n;
            }
        }while(i!=st);
        return ;
    }

    void resize_(){
        vector<uint64_t> v(n);
        
        
        int j = st;
        for(int i=0 ; i<n ; i++){
            int t = MurmurHash64A( &keys[j], sizeof(uint64_t),0)%n;
            if(keys[j] == 0 || keys[j] == UINT64_MAX){
                j++;
                i--;
                j= j%n;
                continue;
            }
            if(i < t){
                i= t;
                if(v[i]==UINT64_MAX)continue;
                v[i] = keys[j]; 
                j++;
                j= j%n;
                continue;
            }
            if(v[i]==UINT64_MAX)continue;
            v[i]= keys[j];
            j++;
            j= j%n;
        }
        int left=0;
        if(j==0)j= n-1;
        else
        j--;
        int h=j;
        while(h!=st){
            if(keys[h] == 0 || keys[h] == UINT64_MAX){
                h++;
                h= h%n;
                continue;
            }    
            left++;
            h++;
            h= h%n;
        }
        
       // cout<<" left"<<left<<"j"<<j<<endl;
        if(left == 0){
            for(int i=0;i<n;i++){
                keys[i]= v[i];
            }
          return ;  
        }
        int k= 0;
        while(left!=0){
            if(v[k]==0){
                left--;
            }
            k++;
        }
        k--;
        // cout<<"k"<<k<<"  "<<endl;

        // for(int p=0;p<n;p++){
        //     cout<<v[p]<<"  ";
        // }
        // cout<<endl;
        // for(int p=0;p<n;p++){
        //     cout<<keys[p]<<" == "<<(MurmurHash64A(&keys[p], sizeof(uint64_t), 0)%n)<<endl;
        // }
        // cout<<endl;
        int tempst;
        int i= k;
        while(1){
            if(v[i]==0 || v[i]== UINT64_MAX){
                if(i==0)break;
                i--;
            }
            else{
                if(v[k]==UINT64_MAX){
                    k--;
                    continue;
                }
                v[k]= v[i];
                
                tempst = k;
                k--;
                if(i==0)break;
                i--;
                
            } 
        }

         i=0;
         while(j!=st){
            if(v[i] == UINT64_MAX){
                i++;
                continue;
            }
            else{
                if(keys[j]==0|| keys[j]==UINT64_MAX){
                    j++;
                    j= j%n;
                    continue;
                }
                v[i]= keys[j];
                j++;
                j= j%n;
                i++;

            }
        }
        for(int i=0;i<n;i++){
            keys[i]= v[i];
        }
        st = tempst;
        //cout<<"fnst"<<st;
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