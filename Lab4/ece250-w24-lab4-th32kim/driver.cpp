// include libraries here
#include <iostream>
#include <string>
#include "graph.h"


int main(){
    
    Graph ER;
    std::string input="";
    int input_a=0;
    int input_b=0;
    double input_d=0;
    double input_s=0;
    double input_A=0;
    std::string filename="";

    do{
        std::cin>>input;
        if(input!="exit"){
            if(input=="insert"){
                std::cin>>input_a;
                std::cin>>input_b;
                std::cin>>input_d;
                std::cin>>input_s;
                ER.insert(input_a,input_b,input_d,input_s);
                std::cout<<"success"<<std::endl;
            }else if(input=="load"){
                std::cin>>filename;
                ER.load(filename);
            }else if(input=="traffic"){
                std::cin>>input_a;
                std::cin>>input_b;
                std::cin>>input_A;
                if(ER.traffic(input_a,input_b,input_A)){
                    std::cout<<"success"<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            }else if(input=="update"){
                std::cin>>filename;
                ER.update(filename);
            }else if(input=="print"){
                std::cin>>input_a;
                ER.print(input_a);
            }else if(input=="delete"){
                std::cin>>input_a;
                ER.Delete(input_a);
            }else if(input=="path"){
                std::cin>>input_a;
                std::cin>>input_b;
                ER.path(input_a,input_b);
            }else if(input=="lowest"){
                std::cin>>input_a;
                std::cin>>input_b;
                ER.lowest(input_a,input_b);
            }
        }

    }while(input!="exit");

}