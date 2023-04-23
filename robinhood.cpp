#include<iostream>
#include<vector>
#include "hashutil.h"

using namespace std;

class Robinhood_Hash{
    vector<uint64_t> keys ;
    //vector<uint64_t> values;
    vector<uint64_t> hv;
    uint64_t hvt;
    size_t n;
    int st;
    //tombstones are uint64_max;
    public:
    Robinhood_Hash(size_t tn){
         n= tn;
        st = 0 ;
        keys.resize(n);
        //values.resize(n);
        n= tn;
        hv.resize(n);
      
        st=0;
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
            int temp = hv[i];
            if(keys[i] == x)return 1;
            else if(keys[i] == 0 ){return 0;
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
    
    int insert_(uint64_t x){
        int hops=0;
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
        uint64_t ind;
        bool b=0;
        if(hashval>= st){
            uint64_t i=hashval;
            uint64_t tp, tpv;
            do{
                int key= keys[i];
                uint64_t temp = hv[i];
                if(keys[i] == 0 || keys[i]==UINT64_MAX){
                    if(keys[i] == 0){
                        if(b){
                            keys[i] = tp;
                            hv[i]=  tpv;
                            keys[ind] =x;
                            hv[ind]= hashval;
                            hops++;

                            return hops; ; 
                        }
                        else{
                            keys[i]= x;
                            hv[i] = hashval;
                            hops++;
                            return hops;
                        }
                    }
                    else{
                        if(b){
                            keys[i] = tp;
                            hv[i] = tpv;
                            keys[ind] =x;
                            hv[ind]= hashval;
                            hops++;
                            return hops; 
                        }
                        else{
                            uint64_t j = (i+1)%n;
                            int tind = i, hvind = 0;
                            bool b2= 0;
                            do{
                                uint64_t temp2= hv[j];
                                if(keys[j]==UINT64_MAX){
                                    if((keys[(j+1)%n]!=0 && keys[(j+1)%n]!=UINT64_MAX) ){
                                        if(b2==0){
                                        
                                        }
                                        else if(hv[(j+1)%n]!=hvind){
                                        keys[tind] =keys[(j)];
                                        hv[tind] = hv[(j)];
                                        tind= j;
                                        hvind= hv[(j+1)%n];}
                                    }
                                    j++;j=j%n;
                                    hops++;
                                    continue;
                                }
                                else if(keys[j]== 0){hops++;break;}
                                else if(b==0 && temp2 > hashval){
                                    hops++;
                                    break;
                                }
                                else{
                                    if(b2==0){
                                        hvind =temp2;
                                        b2=1;
                                        if( hv[(j+1)%n]!=hvind){
                                        keys[tind] =keys[(j)];
                                        hv[tind] = hv[(j)];
                                        tind= j;
                                        hvind= hv[(j+1)%n];
                                        }
                                    }
                                    else if( hv[(j+1)%n]!=hvind){
                                        keys[tind] =keys[(j)];
                                        hv[tind] = hv[(j)];
                                        tind= j;
                                        hvind= hv[(j+1)%n];
                                    }
                                    
                                }
                                j++;
                                if(j==n)j=0;
                                hops++;
                            }while(j!=st);
                            
                                if(j==0)
                                    j=n-1;
                                else
                                    j--;
                                keys[tind] = keys[j];
                                hv[tind] = hv[j];
                                keys[j]=x;
                                hv[j] = hashval;
                                
                                return hops;
                        }
                    }
                }
                else if(b==0 && temp > hashval ){
                    ind= i;
                    b=1;
                    tp= keys[i];
                    tpv= temp;
                }
                else if(b==1){
                    if(tpv ==  temp ){i++;hops++;i=i%n;continue;}
                    uint64_t to= keys[i], tov= temp;
                    keys[i]= tp;
                    hv[i] = tpv;
                    tp= to;
                    tpv= tov;
                }
                i++;
                hops++;
                if(i==n) i=0;
            }while(i!= st);
            uint64_t kp= keys[st], kpv= hv[st];
            for(int i=st;i!=hashval;i++){
                if(i==n)i=0;
                if(keys[i]== 0 || keys[i]==UINT64_MAX){
                    keys[i]=  kp;
                    hv[i]= kpv;
                    hops++;
                    break;
                }
                else{
                    if(hv[i]!=kpv){
                    uint64_t y= keys[i], yv= hv[i];
                    keys[i] = kp;
                    hv[i] = kpv;
                    kp= y;
                    kpv= yv;
                    }
                }
                hops++;
            }
            st= st+1;
            st= st%n;
            uint64_t end= (st==0)?n-1:st-1;
            if(b){
                keys[end] = tp;
                hv[end]= tpv;
                keys[ind]= x;
                hv[ind] = hashval;
                return hops;
            }
            else{
                keys[end] = x;
                hv[end] = hashval;
                return hops;
            }
            cout<<"No FREE SLOTS";
        }
        else{
            uint64_t i=st;
            uint64_t tp, tpv;
            do{
                int key= keys[i];
                uint64_t temp = hv[i];
                if(keys[i] == 0 || keys[i]==UINT64_MAX){
                    if(keys[i] == 0){
                        if(b){
                            keys[i] = tp;
                            hv[i]=  tpv;
                            keys[ind] =x;
                            hv[ind]= hashval;
                            hops++;

                            return hops; ; 
                        }
                        else{
                            keys[i]= x;
                            hv[i] = hashval;
                            hops++;
                            return hops;
                        }
                    }
                    else{
                        if(b){
                            keys[i] = tp;
                            hv[i] = tpv;
                            keys[ind] =x;
                            hv[ind]= hashval;
                            hops++;
                            return hops; 
                        }
                        else{
                            uint64_t j = (i+1)%n;
                            int tind = i, hvind = 0;
                            bool b2= 0;
                            do{
                                uint64_t temp2= hv[j];
                                if(keys[j]==UINT64_MAX){
                                    if((keys[(j+1)%n]!=0 && keys[(j+1)%n]!=UINT64_MAX) ){
                                        if(b2==0){
                                        
                                        }
                                        else if(hv[(j+1)%n]!=hvind){
                                        keys[tind] =keys[(j)];
                                        hv[tind] = hv[(j)];
                                        tind= j;
                                        hvind= hv[(j+1)%n];}
                                    }
                                    j++;j=j%n;
                                    hops++;
                                    continue;
                                }
                                else if(keys[j]== 0){hops++;break;}
                                else if(b==0 && temp2 > hashval){
                                    hops++;
                                    break;
                                }
                                else{
                                    if(b2==0){
                                        hvind =temp2;
                                        b2=1;
                                        if( hv[(j+1)%n]!=hvind){
                                        keys[tind] =keys[(j)];
                                        hv[tind] = hv[(j)];
                                        tind= j;
                                        hvind= hv[(j+1)%n];
                                        }
                                    }
                                    else if( hv[(j+1)%n]!=hvind){
                                        keys[tind] =keys[(j)];
                                        hv[tind] = hv[(j)];
                                        tind= j;
                                        hvind= hv[(j+1)%n];
                                    }
                                    
                                }
                                j++;
                                if(j==n)j=0;
                                hops++;
                            }while(j!=st);
                            
                                if(j==0)
                                    j=n-1;
                                else
                                    j--;
                                keys[tind] = keys[j];
                                hv[tind] = hv[j];
                                keys[j]=x;
                                hv[j] = hashval;
                                
                                return hops;
                        }
                    }
                }
                else if(b==0 && temp > hashval ){
                    ind= i;
                    b=1;
                    tp= keys[i];
                    tpv= temp;
                }
                else if(b==1){
                    if(tpv ==  temp ){i++;hops++;i=i%n;continue;}
                    uint64_t to= keys[i], tov= temp;
                    keys[i]= tp;
                    hv[i] = tpv;
                    tp= to;
                    tpv= tov;
                }
                i++;
                hops++;
                if(i==n) i=0;
            }while(i!= st);
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
            if(keys[i] == x){
                int j = (i+1)%n;
                do{
                    int t2 =  hv[j];
                    if(t2 == j){
                        int p = j==0? n-1:j-1;
                        keys[p]= 0;
                        hv[p] = 0;
                        break;
                    }
                    int p = j==0? n-1:j-1;
                    keys[p]= keys[j];
                    hv[p] = hv[j];
                    keys[j]=0;
                    hv[j] = 0;
                    j++;
                    j= j%n;
                }while(j!=st);
                return ;
            }
            else if(keys[i] == 0 ){return ;
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
    void print(){
     //   cout<<tot<<" total "<<endl;
        for(int i=0;i<100;i++){
            cout<<i << " == "<<keys[i]<<"        ";
        }
    }
    void print2(){
    //    cout<<tot<<" total "<<endl;
        for(int i=0;i<100;i++){
            cout<<MurmurHash64A(&keys[i],sizeof(uint64_t),0)%n<<"        ";
        }
    } 
};