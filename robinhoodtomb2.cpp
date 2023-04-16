#include<iostream>
#include<vector>
#include "hashutil.h"
#include<unordered_map>

using namespace std;

class Robinhoodtomb_Hash{
    vector<uint64_t> keys ;
   // vector<uint64_t> values;
    vector<uint64_t> hv;
    uint64_t hvt ;
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
        hv.resize(n);
      //  values.resize(n);
        uint64_t c= UINT64_MAX;
        hvt= MurmurHash64A(&c, sizeof(uint64_t), 0)%n;
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
            int temp =  hv[i];
            if(keys[i] == x)return 1;
            else if(keys[i] == 0 ){return 0;
            }
            else if(keys[i] == UINT64_MAX){
                i++;
                if(i==n)i=0;
            }
            else if(temp > hashval ){
                return 0;
            }
            else{
                i++;
                if(i==n)i=0;
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
                int temp = hv[i];
                if(keys[i] == 0 || keys[i]==UINT64_MAX){
                    if(keys[i] == 0){
                        if(b){
                            for(int k= i;k!=ind;k=(k==0?n-1:k-1) ){
                                
                                int t=k-1;;
                                 if(k==0){
                                    t=n-1;
                                 }
                                keys[k] =keys[t];
                                hv[k]= hv[t];
                            }
                            keys[ind] =x;
                            hv[ind]= hashval;
                            return ; 
                        }
                        else{
                            keys[i]= x;
                            hv[i] = hashval;
                            return ;
                        }
                    }
                    else{
                        if(b){
                            for(int k= i;k!=ind;k=(k==0?n-1:k-1) ){
                                 int t=k-1;;
                                 if(k==0){
                                    t=n-1;
                                 }
                                 keys[k] =keys[t];
                                 hv[k]= hv[t];
                            }
                            keys[ind] =x;
                            hv[ind]= hashval;
                            return ; 
                        }
                        else{
                            int j= i;
                            do{
                                int temp2= hv[j];
                                if(keys[j]==UINT64_MAX){j++;j=j%n;continue;}
                                else if(keys[j]== 0){break;}
                                else if(b==0 && temp2 > hashval){
                                    break;
                                }
                                j++;
                                if(j==n)j=0;
                            }while(j!=st);
                            
                                if(j==0)
                                    j=n-1;
                                else
                                    j--;

                                for(int k = i;k!= j;k=(k+1)%n ){
                                   int temp= (k+1);
                                   if(temp== n)temp=0;
                                    keys[k]= keys[temp];
                                    hv[k] =  hv[(temp)];
                                }
                                keys[j]=x;
                                hv[j] = hashval;
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
                if(i==n) i=0;
            }while(i!= st);

            for(int i=st;i!=hashval;i++){
                if(i==n)i=0;
                if(keys[i]== 0 || keys[i]==UINT64_MAX){
                    int k=i;
                    while(k>st){
                        int t= (k==0 ? n-1:k-1);
                        keys[k]= keys[t];
                        hv[k]= hv[t];
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
                    hv[k] = hv[t];
                    if (k==0)k=n-1;
                    else
                    k--;
                }
                keys[ind]= x;
                hv[ind] = hashval;
                return ;
            }
            else{
                keys[st-1] = x;
                hv[st-1] = hashval;
                return;
            }
            cout<<"No FREE SLOTS";
        }
        else{
            int i= st;
            int temp, tempv;
            do{
                int t2= hv[i];
                if(keys[i] == 0|| keys[i]==UINT64_MAX){
                    if(keys[i]==0){
                        if(b){
                            keys[i] = temp;
                            hv[i] = tempv;
                            keys[ind]= x;
                            hv[ind] = hashval;
                            return ;
                        }
                        else{
                            keys[i] = x;
                            hv[i] = hashval;
                            return ;
                        }
                    }
                    else{
                        if(b){
                            keys[i] = temp;
                            hv[i] = tempv;
                            keys[ind]= x;
                            hv[ind] = hashval;
                            return ;
                        }
                        else{
                            int j= i;
                            do{
                                int temp3= hv[j];
                                if(keys[j] == 0 ||keys[j]==UINT64_MAX){
                                    if(keys[j] == 0)break;
                                    keys[j] = keys[(j+1)%n];
                                    hv[j]= hv[(j+1)%n];
                                    j++;
                                    j= j%n;
                                    continue;
                                }
                                else if(temp3 > hashval ){
                                    break;
                                }
                                else {
                                    keys[j] = keys[(j+1)%n];
                                    hv[j]= hv[(j+1)%n];
                                }
                                j++;
                                if(j==n)j=0;
                            }while(j!=st);
                            if(j ==0){
                                j=n-1;
                            }
                            else j--;
                            
                            keys[j] = x;
                            hv[j] = hashval;
                            return ;
                        }
                    }
                }
                else if( b==0 && t2 > hashval){
                    ind= i;
                    b=1;
                    temp = keys[i];
                    tempv = t2;
                }
                else if(b==1){
                    int to= keys[i], tov= hv[i];
                    keys[i] = temp;
                    hv[i]= tempv;
                    temp=  to;
                    tempv= tov;
                }
                i++;
                if(i==n)i=0;
            }while(i!=st);
        }
    }
    void delete_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
        int i;
        if(hashval < st){
            i = st; 
        }
        else
            i= hashval;
        do{
            int temp =  hv[i];
            if(keys[i] == x){keys[i]=UINT64_MAX;
            hv[i] = hvt;
            return ;}
            else if(keys[i] == 0 ){return ;
            }
            else if(keys[i] == UINT64_MAX){
                i++;
                if(i==n)i=0;
            }
            else if(temp > hashval ){
                return ;
            }
            else{
                i++;
                if(i==n)i=0;
            }
        }while(i!=st);
        return ;
    }

    void resize_(){
        vector<uint64_t> v(n);
        vector<uint64_t> vhv(n);
        
        int j = st;
        for(int i=0 ; i<n ; i++){
            int t = hv[j];
            if(keys[j] == 0 || keys[j] == UINT64_MAX){
                j++;
                i--;
                if(j==n)j=0;
                continue;
            }
            if(i < t){
                i= t;
                if(v[i]==UINT64_MAX)continue;
                v[i] = keys[j]; 
                vhv[i]= hv[j];
                j++;
                if(j==n)j=0;
                continue;
            }
            if(v[i]==UINT64_MAX)continue;
            v[i]= keys[j];
            vhv[i]= hv[j];
            j++;
            if(j==n)j=0;
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
            if(h==n) h=0;
        }
        
       // cout<<" left"<<left<<"j"<<j<<endl;
        if(left == 0){
            for(int i=0;i<n;i++){
                keys[i]= v[i];
                hv[i]= vhv[i];
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
                vhv[k]= vhv[i];
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
                    if(j==n)j=0;
                    continue;
                }
                v[i]= keys[j];
                vhv[i]= hv[j];
                j++;
                if(j==n)j=0;
                i++;

            }
        }
        for(int i=0;i<n;i++){
            keys[i]= v[i];
            hv[i]= vhv[i];
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