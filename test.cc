#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <string>
#include<unordered_map>
//#include <openssl/rand.h>

#include "graveyardhashing_AT.cpp"
#include "robinhood.cpp"
#include "robinhood_TOMB.cpp"
#pragma include<unordered_map>

using namespace std;
using namespace std::chrono;
//auto diff = std::chrono::high_resolution_clock::now() - start; // get difference 
//auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
double elapsed(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2) {
	return (duration_cast<duration<double>>(t2 - t1)).count();
}

/*This is used for teting purposes but as we want large data storing this will take lots of space. Hence we are doing operation
in order x, x+1, x+2,...... . As we are inserting based on hashvalue randomness is maintained in this too.
*/
// void safe_rand_bytes(unsigned char *v, uint32_t n) {
// 	while (n > 0) {
// 		size_t round_size = n >= INT_MAX ? INT_MAX - 1 : n;
// 		RAND_bytes(v, round_size);
// 		v += round_size;
// 		n -= round_size;
// 	}
// }

int main(){
     ofstream myFile;
     myFile.open("test_25M.csv");
    myFile<<"Iterations"<<","<<"D-RH"<<","<<"D-RHT"<<","<<"D-GH"<<",D-UMAP"<<","<<"I-RH"<<","<<"I-RHT"<<","<<"I-GH"<<",I-UMAP"<<",Q-RH"<<",Q-RHT"<<",Q-GH"<<",Q-UMAP"<<",Hops-RH"<<",Hops-RHT"<<",Hops-GH"<<endl;
    // change values of these based on requiremets
    int table_size= 25000000;
    int per_90 =22500000;
    int per_point14= 360900;
    high_resolution_clock::time_point t1, t2;

    Robinhood_Hash *ob1 = new Robinhood_Hash(table_size);
    Robinhoodtomb_Hash *ob2 = new Robinhoodtomb_Hash(table_size);
    Graveyard_Hash *ob3 = new Graveyard_Hash(table_size);
    unordered_map<uint64_t,uint64_t> umap;
    umap.rehash(table_size); 

    t1 = high_resolution_clock::now();
    for(int i=1;i<=per_90;i++){
        ob1->insert_(i);
    }
   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 90 percent items : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    t1 = high_resolution_clock::now();
    for(int i=1;i<=per_90;i++){
        ob2->insert_(i);
    }
   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 90 percent items : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    t1 = high_resolution_clock::now();
    for(int i=1;i<=per_90;i++){
        ob3->insert_(i);
    }

   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 90 percent items  : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    t1 = high_resolution_clock::now();
    for(int i=1;i<=per_90;i++){
        umap[i] =i;
    }

   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 90 percent items umap : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    int add_st=per_90+1, del_st=1;
    cout<<endl;
    int k = 0;
    double sum2=0, sum3=0;
    for(int j=0;j<1000;j++){
        //DELETION
        int tot1=0, tot2=0, tot3=0;
        double s1,s2, s3, s4,s5,s6,s7,s8,s9, s10, s11, s12;
        std::cout<<j<<"   ";
        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+per_point14;i++){
            ob1->delete_(i);
        }
        t2 = high_resolution_clock::now();
        s1=elapsed(t1, t2);
        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+per_point14;i++){
            ob2->delete_(i);
        }
        t2 = high_resolution_clock::now();
        s2=elapsed(t1, t2);

        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+per_point14;i++){
            ob3->delete_(i);
        }
        t2 = high_resolution_clock::now();
        s3=elapsed(t1, t2);
        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+per_point14;i++){
            umap.erase(i);
        }
        t2 = high_resolution_clock::now();
        s10=elapsed(t1, t2);
        del_st= del_st+per_point14;
        if(k%8 == 0){
            t1 = high_resolution_clock::now();
            ob2->resize_();
            t2 = high_resolution_clock::now();
            sum2= elapsed(t1, t2);
            sum2= sum2/8;
            t1 = high_resolution_clock::now();
            ob3->resize_();
            t2 = high_resolution_clock::now();
            sum3= elapsed(t1, t2);
            sum3= sum3/8;
        }
        k++;
        //INSERTION
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+per_point14;i++){
            tot1+=ob1->insert_(i);
        }
        t2 = high_resolution_clock::now();
        s4 = elapsed(t1,t2);
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+per_point14;i++){
            tot2+=ob2->insert_(i);
        }
        t2 = high_resolution_clock::now();
        s5=elapsed(t1, t2);

        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+per_point14;i++){
            tot3+=ob3->insert_(i);
        }
        t2 = high_resolution_clock::now();
        s6=elapsed(t1, t2);

        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+per_point14;i++){
            umap[i]=i;
        }
        t2 = high_resolution_clock::now();
        s11=elapsed(t1, t2);


        //QUERY
                
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+per_point14;i++){
            if(ob1->query_(i)){}
            else cout<<i<<"error"<<"===="<<endl;
        }
        t2 = high_resolution_clock::now();
        s7 = elapsed(t1,t2);
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+per_point14;i++){
            if(ob2->query_(i)){}
            else cout<<i<<"error"<<"=="<<endl;;
        }
        t2 = high_resolution_clock::now();
        s8=elapsed(t1, t2);

        t1 = high_resolution_clock::now();

        for(int i=add_st;i<add_st+per_point14;i++){
            if(ob3->query_(i)){}
            else cout<<i<<" error"<<"==="<<endl;
        }
        t2 = high_resolution_clock::now();
        s9=elapsed(t1, t2);


        t1 = high_resolution_clock::now();

        for(int i=add_st;i<add_st+per_point14;i++){
            if(umap[i]=i){}
            else cout<<i<<" error"<<"==="<<endl;
        }
        t2 = high_resolution_clock::now();
        s12=elapsed(t1, t2);

        add_st = add_st+per_point14;

        myFile<<j+1<<","<<s1<<","<<s2<<","<<s3<<","<<s10<<","<<s4<<","<<s5+sum2<<","<<s6+sum3<<","<<s11<<","<<s7<<","<<s8<<","<<s9<<","<<s12<<","<<tot1<<","<<tot2<<","<<tot3<<endl;
    }

    return 1;
}
