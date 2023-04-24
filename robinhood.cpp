#include<iostream>
#include<vector>
#include "hashutil.h"

using namespace std;

class Robinhood_Hash{
    vector<uint64_t> keys ; //stores the keys values in this vector
    //vector<uint64_t> values;
    vector<uint64_t> hv;  //stores the hashvalue of corresponding keys in this
    uint64_t hvt;   //stores hash value of tombstone
    size_t n;   // size of hash table
    int st;     // start point of hash table
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
        // based on hash value setting the iteration point start
        if(hashval < st){
            i = st; 
        }
        else
            i= hashval;
        // loops until element found(ret 1), empty slot hashval greater than our hashval(ret 0);
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
        //hops store the number of iterations done to insert an element (indexes travelled)
        int hops=0;
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
        // these values are used in shifting data
        uint64_t ind;
        bool b=0;
        if(hashval>= st){
            uint64_t i=hashval;
            uint64_t tp, tpv; // temp values used in shifting
            // loop runs until a free slot found
            do{
                int key= keys[i];
                uint64_t temp = hv[i];
                // if keys[i] is 0 then shift and insert happens, if tombstone then maybe we have to iterate more
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
                        
                    }
                }
                else if(b==0 && temp > hashval ){
                    // in case before we find empty slot we find the hashval greater than x hash value
                    ind= i;
                    b=1;
                    tp= keys[i];
                    tpv= temp;
                }
                else if(b==1){
                    // shifting of data
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
            // in case no free slot found then we have to shift the start so that a extra space is there at end
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
                // if keys[i] is 0 then shift and insert happens, if tombstone then maybe we have to iterate more
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
                        
                    }
                }
                else if(b==0 && temp > hashval ){
                    // in case before we find empty slot we find the hashval greater than x hash value
                    ind= i;
                    b=1;
                    tp= keys[i];
                    tpv= temp;
                }
                else if(b==1){
                    // shifting of data
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
        return hops;
    }
    
    void delete_(uint64_t x){
        uint64_t hashval = MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
        int i;
        //set the start point of iteration based on hashvalue of x
        if(hashval < st){
            i = st; 
        }
        else
            i= hashval;
        // just like query it loops, here they put tombstone when element found
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
    
};