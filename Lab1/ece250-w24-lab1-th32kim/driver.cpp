// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "game.h"


int main(){
    
    //your code goes here...  
    LinkedList Test;
    Test.Spawn(0,-1);
    // Test.Spawn(-1,0);
    // Test.Spawn(-1,-1);
    // Test.Spawn(2,3);
    // Test.Spawn(5,100);
    // Test.Spawn(6,99);
    Test.display();
    return 0;
}