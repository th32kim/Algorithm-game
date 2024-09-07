// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <sstream>
#include "tokenize.h"


int main(){
    BiHashTable HashMap;
    std::string input="";
    std::string param="";
    int num_param=0;

    do{
        std::cin>>input;
        if(input!="exit"){
            if(input=="create"){
                std::cin>>num_param;
                HashMap.Create(num_param);
            }else if(input=="insert"){
                std::cin>>param;
                if(HashMap.insert(param)){
                    std::cout<<"success"<<std::endl;
                }else{
                    std::cout<<"failure"<<std::endl;
                }
            }else if(input=="load"){
                std::cin>>param;
                HashMap.Load(param);
            }else if(input=="tok"){
                std::cin>>param;
                std::cout<<HashMap.tok(param)<<std::endl;
            }else if(input=="ret"){
                std::cin>>num_param;
                HashMap.ret(num_param);
                std::cout<<std::endl;
                
            }else if(input=="tok_all"){
                //loop checking if there is no more white space(end of the input)
                std::string input_field;
                std::getline(std::cin,input_field);
                std::istringstream inputs(input_field);
                while(inputs>>param){
                    std::cout<<HashMap.tok(param)<<" ";
                }
                std::cout<<std::endl;
            }else if(input=="ret_all"){
                bool indent=false;
                std::string input_field;
                std::getline(std::cin,input_field);
                std::istringstream inputs(input_field);
                while(inputs>>num_param){
                    if(HashMap.ret(num_param)){
                        indent = true;
                    }
                    std::cout<<" ";
                }
                if(indent){
                    std::cout<<std::endl;
                }
            }else if(input=="print"){
                std::cin>>num_param;
                HashMap.print(num_param);
            }
        }

    }while(input!="exit");



}