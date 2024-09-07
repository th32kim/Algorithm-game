#include "game.h"
#include <cmath>
#include <iostream>

// implement classes' member functions here...

//Node Constructor
LinkedList::Node::Node(double input_x, double input_y){
    x = input_x;
    y = input_y;
    next = nullptr;
    distance = sqrt((x*x)+(y*y));
}

//Linked List constructor - setting head pointer to null (default at the start)
LinkedList::LinkedList(){
    head = nullptr;
    tail = nullptr;
    numPlayer = 0;
}

//Spawn Function, output success or failure depending on the input
void LinkedList::Spawn(double spawn_x, double spawn_y){
    //Attempt to start outside the first quadrant
    if(spawn_x<=0||spawn_y>=0){
        std::cout<<"failure"<<std::endl;
    }else{
        Node* newPlayer = new Node(spawn_x,spawn_y);
        //No existing node, adding from the top(head)
        if(tail==nullptr){
            head=tail=newPlayer;
        }else{
            //Link already exist, adding player to the back, updating tail pointer
            tail->next=newPlayer;
            tail=newPlayer;
        }
        std::cout<<"success"<<std::endl;
        //Update the player number of players;
        numPlayer++;
    }
}

////Num function, output number of players playing the game
void LinkedList::Num(){
    std::cout<<"num of players: "<<numPlayer<<std::endl;
}

//Over Function, print out the result of the game
void LinkedList::OVER(){
    if(numPlayer==0){
        std::cout<<"wolf wins"<<std::endl;
    }else{
        std::cout<<"players win"<<std::endl;
    }
}
void LinkedList::display(){
    LinkedList test;
        Node* current = head;
        while (current != nullptr) {
            std::cout<<"Player info : ";
            std::cout << "x-val: "<<current->x<<std::endl;
            std::cout << " y-val: "<<current->y;
            std::cout << " distance: "<<current->distance;
            current = current->next;
        }
        std::cout<<"Player remaining: ";
        test.Num();
        std::cout << std::endl;
}
//Linked List Destructor - deleting the linked list
LinkedList::~LinkedList(){
    while(head!=nullptr){
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    delete tail;
}