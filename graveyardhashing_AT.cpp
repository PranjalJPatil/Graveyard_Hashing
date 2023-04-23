#include<iostream>
#include<vector>
#include "hashutil.c"
#include<unordered_map>

using namespace std;

class Graveyard_Hash{
    vector<uint64_t> keys ;
    //vector<uint64_t> values ;
    uint64_t st ;
    vector<uint64_t> hv;
    uint64_t hvt;
    int tot=0 ;
    size_t  n ;
    int lf;
    int k =0 ;
    //tombstones are uint64_max;
    public:
    Graveyard_Hash(size_t kn){
        n= kn;
        lf = 15 ;
        st = 0 ;
        keys.resize(n);
       // values.resize(n);
        hv.resize(n);
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
            uint64_t temp =  hv[i];
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
        for(int i=0;i<n;i+=lf){
            v[i] =UINT64_MAX;
            vhv[i] =hvt;
        }
        int j = st;
        int i=0;
        
        do{
            uint64_t tj = hv[j];
            if(keys[j] ==  UINT64_MAX || keys[j]== 0){
                j++;
                j= j%n;
                if(j==st){break;}

            }
            else if(tj > i){
                i= tj ;
                if(v[i]==UINT64_MAX){i++;continue;}
                v[i]=keys[j];
                vhv[i] = hv[j];
                i++;
                j++;
                j=j%n;
                if(j==st){break;}

            }
            else{
                if(v[i]==UINT64_MAX){i++;continue;}
                v[i]=keys[j];
                vhv[i] = hv[j];
                i++;
                j++;
                j= j%n ;
                if(j==st){break;}
            }
        }while(i!=n );
        int elements = 0;
        int k = j;
        while(k!=st){
            if(keys[k]==0 || keys[k] == UINT64_MAX){
            }else{elements++;}
            k++;
            k= k%n;
        }


        if(elements == 0){
            for(int i=0;i<n;i++){
                keys[i] = v[i];
                hv[i]= vhv[i]; 
            }
            st= 0;
            return ;
        }
        i=0;
        while(i<n && elements!=0){
            if(v[i]==0){
               elements--; 
            }
            i++;
        }
        
        i--;
        k = i;
        int tempst = 0;

        while(1){
            if(v[i] != 0 && v[i]!=UINT64_MAX){
                if(v[k]==0){
                    v[k] = v[i];
                    vhv[k]=vhv[i];
                    tempst = k;
                    v[i] = 0;
                    vhv[i]=0;
                    if(i==0){break;}
                    i--;
                    k--;
                }
                else{
                    k--;
                }
            }
            else{
                if(i==0){break;}
                i--;
                
            }
        }
        
        i=0;
        while(j!=st){
            if(keys[j] == 0 || keys[j] ==UINT64_MAX){}
            else{
                if(v[i]==UINT64_MAX){i++;continue;}
                v[i] = keys[j];
                vhv[i]= hv[j];
                i++;
            }
            j++;
            j= j%n;
        }
        tempst = i;
        for(int i=0;i<n;i++){
            keys[i] = v[i];
            hv[i]= vhv[i]; 
        }
        st= tempst;
    }
    int printhv(uint64_t x){
        return MurmurHash64A(&x, sizeof(uint64_t), 0)%n;
    }
    bool ccc(){
        int i=st;
        int bef ;
        bool b=0;
        do{
            if(keys[i] == 0 || keys[i]==UINT64_MAX){
                
            }
            else{
                if(b==0){
                    bef= hv[i];
                    b=1;
                }
                else{
                if(hv[i]>= bef){
                    bef= hv[i];
                }
                else{return 1;}
                }
            }
            i++;
            i= i%n;
        }while(i!=st);
        return 0;
    }
    void print(){
        cout<<st<<" total "<<endl;
        for(int i=0;i<n;i++){
            cout<<i<<"==="<<keys[i]<<"===="<<MurmurHash64A(&keys[i], sizeof(uint64_t), 0)%n<<"==="<<hv[i]<<endl;
        }
    }
    void print2(uint64_t i){
        cout<<i<<"==="<<"===="<<MurmurHash64A(&i, sizeof(uint64_t), 0)%n<<"==="<<endl;
    } 
};