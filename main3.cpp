#include<iostream>
#include<fstream>
#include <chrono>
#include<vector>
#include <string>
#include<unordered_map>
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
int main(){
     ofstream myFile;
     myFile.open("test_100K_lf.csv");
    myFile<<"Iterations"<<","<<"D-RH"<<","<<"D-RHT"<<","<<"D-GH"<<",D-UMAP"<<","<<"I-RH"<<","<<"I-RHT"<<","<<"I-GH"<<",I-UMAP"<<",Q-RH"<<",Q-RHT"<<",Q-GH"<<",Q-UMAP"<<",Hops-RH"<<",Hops-RHT"<<",Hops-GH"<<endl;

    high_resolution_clock::time_point t1, t2;

    Robinhood_Hash *ob1 = new Robinhood_Hash(26622316);
    Robinhoodtomb_Hash *ob2 = new Robinhoodtomb_Hash(26622316);
    Graveyard_Hash *ob3 = new Graveyard_Hash(26622316);
    unordered_map<uint64_t,uint64_t> umap;
    umap.rehash(25000000); 

    t1 = high_resolution_clock::now();
    for(int i=1;i<=23960084;i++){
        ob1->insert_(i);
    }
   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 100000 items : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    t1 = high_resolution_clock::now();
    for(int i=1;i<=23960084;i++){
        ob2->insert_(i);
    }
   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 100000 items : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    t1 = high_resolution_clock::now();
    for(int i=1;i<=23960084;i++){
        ob3->insert_(i);
    }

   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 100000 items po : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    t1 = high_resolution_clock::now();
    for(int i=1;i<=23960084;i++){
        umap[i] =i;
    }

   	t2 = high_resolution_clock::now();
	std::cout << "Time insert 100000 items umap : " + std::to_string(elapsed(t1, t2)) + " secs\n";
    int add_st=23960085, del_st=1;
    cout<<endl;
    int k = 0;
    double sum2=0, sum3=0;
    for(int j=0;j<2000;j++){
        //DELETION
        int tot1=0, tot2=0, tot3=0;
        double s1,s2, s3, s4,s5,s6,s7,s8,s9, s10, s11, s12;
        std::cout<<j<<"   ";
        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+1331115;i++){
            ob1->delete_(i);
        }
        t2 = high_resolution_clock::now();
        //std::cout << "Time delete 5000 items Robinhood_Hash : " + std::to_string(elapsed(t1, t2)) + " secs\n";
        s1=elapsed(t1, t2);
        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+1331115;i++){
            ob2->delete_(i);
        }
        t2 = high_resolution_clock::now();
        //std::cout << "Time delete 5000 items Robinhoodtomb_Hash : " + std::to_string(elapsed(t1, t2)) + " secs\n";
        s2=elapsed(t1, t2);

        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+1331115;i++){
            ob3->delete_(i);
        }
        t2 = high_resolution_clock::now();
        s3=elapsed(t1, t2);
        t1 = high_resolution_clock::now();
        for(int i=del_st;i<del_st+1331115;i++){
            umap.erase(i);
        }
        t2 = high_resolution_clock::now();
        s10=elapsed(t1, t2);
        //std::cout << "Time delete 5000 items Graveyard_Hash: " + std::to_string(elapsed(t1, t2)) + " secs\n";
        del_st= del_st+1331115;
        if(k%3 == 0){
            t1 = high_resolution_clock::now();
            ob2->resize_();
            t2 = high_resolution_clock::now();
            sum2= elapsed(t1, t2);
            sum2= sum2/3;
            t1 = high_resolution_clock::now();
            ob3->resize_();
            t2 = high_resolution_clock::now();
            sum3= elapsed(t1, t2);
            sum3= sum3/3;
        }
        k++;
        //INSERTION
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+1331115;i++){
            tot1+=ob1->insert_(i);
        }
        t2 = high_resolution_clock::now();
       // std::cout << "Time insert 5000 items Robinhood_Hash : " + std::to_string(elapsed(t1, t2)) + " secs\n";
        s4 = elapsed(t1,t2);
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+1331115;i++){
            tot2+=ob2->insert_(i);
        }
        t2 = high_resolution_clock::now();
       // std::cout << "Time insert 5000 items Robinhoodtomb_Hash : " + std::to_string(elapsed(t1, t2)) + " secs\n";
        s5=elapsed(t1, t2);

        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+1331115;i++){
            tot3+=ob3->insert_(i);
        }
        t2 = high_resolution_clock::now();
        s6=elapsed(t1, t2);
        //std::cout << "Time insert 5000 items Graveyard_Hash: " + std::to_string(elapsed(t1, t2)) + " secs\n";

        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+1331115;i++){
            umap[i]=i;
        }
        t2 = high_resolution_clock::now();
        s11=elapsed(t1, t2);
        //std::cout << "Time insert 5000 items Graveyard_Hash: " + std::to_string(elapsed(t1, t2)) + " secs\n";


        //QUERY
                
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+1331115;i++){
            if(ob1->query_(i)){}
            else cout<<i<<"p"<<"===="<<endl;
        }
        t2 = high_resolution_clock::now();
       // std::cout << "Time query 5000 items Robinhood_Hash : " + std::to_string(elapsed(t1, t2)) + " secs\n";
        s7 = elapsed(t1,t2);
        t1 = high_resolution_clock::now();
        for(int i=add_st;i<add_st+1331115;i++){
            if(ob2->query_(i)){}
            else cout<<i<<"k"<<"=="<<endl;;
        }
        t2 = high_resolution_clock::now();
       // std::cout << "Time query 5000 items Robinhoodtomb_Hash : " + std::to_string(elapsed(t1, t2)) + " secs\n";
        s8=elapsed(t1, t2);

        t1 = high_resolution_clock::now();

        for(int i=add_st;i<add_st+1331115;i++){
            if(ob3->query_(i)){}
            else cout<<i<<" r"<<"==="<<endl;
        }
        t2 = high_resolution_clock::now();
        s9=elapsed(t1, t2);
        //std::cout << "Time query 5000 items Graveyard_Hash: " + std::to_string(elapsed(t1, t2)) + " secs\n";


        t1 = high_resolution_clock::now();

        for(int i=add_st;i<add_st+1331115;i++){
            if(umap[i]=i){}
            else cout<<i<<" r"<<"==="<<endl;
        }
        t2 = high_resolution_clock::now();
        s12=elapsed(t1, t2);

        add_st = add_st+1331115;

        myFile<<j+1<<","<<s1<<","<<s2<<","<<s3<<","<<s10<<","<<s4<<","<<s5+sum2<<","<<s6+sum3<<","<<s11<<","<<s7<<","<<s8<<","<<s9<<","<<s12<<","<<tot1<<","<<tot2<<","<<tot3<<endl;
    }

    return 1;
}