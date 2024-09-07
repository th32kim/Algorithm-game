// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"


int main(){
    Trie Spellcheck;
    std::string input ="";
    std::string param ="";
    do{
        std::cin>>input;
        if(input!="exit"){
            if(input=="load"){
                Spellcheck.Load();
            }else if(input=="i"){
                std::cin>>param;
                Spellcheck.Insert(param,true);
            }else if(input=="c"){
                std::cin>>param;
                Spellcheck.Prefix(param);
            }else if(input=="e"){
                std::cin>>param;
                Spellcheck.Erase(param);
            }else if(input=="p"){
                Spellcheck.Print();
            }else if(input=="spellcheck"){
                std::cin>>param;
                Spellcheck.spellcheck(param);
            }else if(input=="empty"){
                Spellcheck.empty();
            }else if(input=="clear"){
                Spellcheck.clear();
            }else if(input=="size"){
                Spellcheck.size();
            }
        }
    }while(input!="exit");
}