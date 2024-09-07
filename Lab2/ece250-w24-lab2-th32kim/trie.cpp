#include "trie.h"
#include <iostream>
#include <string>
#include <fstream>

// implement classes' member functions here...
//TrieNode Constructor
Trie::TrieNode::TrieNode(){
    //Setting all the 'child' node for each Trie node as null by default
    for(int i=0; i<26; i++){
        children[i]=nullptr;
    }
    Lastchar = false;
}

//Trie Constructor
Trie::Trie(){
    root = new TrieNode();
    Trie_Empty = true;
    num_words=0;
}
//Trie Load Function
void Trie::Load(){
    std::ifstream file;
    file.open("corpus.txt");
    std::string word;
    while(!file.eof()){
        file >> word;
        Insert(word,false);
    }
    std::cout<<"success"<<std::endl;
}

//Trie Insert function
void Trie::Insert(std::string word,bool display){
    TrieNode* curr = root; 
    //Looping around the 'children' node to put the alphabet of single character accordingly
    for(std::size_t i=0; i<word.length(); i++){
        int loc = word[i] -'A'; //Extracting 'order' of the character
        if(curr->children[loc]==nullptr){
            //no new character in the extracted character location, adding it to curr child
            curr->children[loc] = new TrieNode();
        }

        curr = curr->children[loc]; //iterating to the next 'character'
    }
    
    if(curr->Lastchar){
        //Duplicated word, do not do any action
        if(display){
            std::cout<<"failure"<<std::endl;
        }
    }else{
        //No duplicate, update the Trie
        //new word added, increasing the total number of words in the trie
        num_words++;
        //loop is done, marking it has reached the last character
        curr->Lastchar = true;
        if(display){
            std::cout<<"success"<<std::endl;
        }
        Trie_Empty=false;
    }
}

//Prefix Function
void Trie::Prefix(std::string prefix){
    TrieNode* curr = root;
    
    //Even though the following for loop might look like O(n), 
    //if there are N number of nodes smaller than n, the loop reaches nullptr at Nth iteration, which then 
    //stops and ends the loop, 
    //guaranteeing it will only run N times making the following O(N)

    for(char c: prefix){
        int loc = c-'A';//Extracting 'order' of the character
        if(curr->children[loc]==nullptr){
            //no word with prefix was found
            std::cout<<"not found"<<std::endl;
            return;
        }
        curr = curr->children[loc];
    }
    int num_prefix = countPrefix(curr);
    std::cout<<"count is "<<num_prefix<<std::endl;

}
//Prefix Helper Function for calculating number of words containing given prefixes
int Trie::countPrefix(TrieNode* node){
    int num = 0;
    //Reached the 'end' of the word without prefix matched
    if(node ==nullptr){
        return 0;
    }

    //Loop around the 'children' of the current node, search for its following matching prefixes
    for(int i=0; i<26; i++){
        num += countPrefix(node->children[i]);
    }

    //Reached the end of the word (containing prefix), increment the count
    if(node->Lastchar){
        num++;
    }

    return num;
}

void Trie::Erase(std::string word){
    if(num_words==0){
        //Empty Trie
        std::cout<<"failure"<<std::endl;
        return;
    }else{
        Erase_helper(root,0,word);
    }
}

void Trie::Erase_helper(TrieNode* node, std::size_t index, const std::string &word){
    int child_index = word[index]-'A';
    TrieNode*& next_node = node->children[child_index];
    //No word is found
    if(next_node==nullptr){
        std::cout<<"failure"<<std::endl;
        return;
    }
    //Iterating until last index of the word is reached
    if(index<word.length()-1){
        Erase_helper(next_node,index+1,word);
    }
    //Finished looping, evaluating whether word is inside the Trie as a complete word
    if(index==word.length()-1){
        //Deleting the word
        if(next_node->Lastchar==false){
            //Word is not found(Word is contained as a prefix, not complete word)
            std::cout<<"failure"<<std::endl;
            return;
        }
        next_node->Lastchar=false;
        num_words--;
        std::cout<<"success"<<std::endl;
        //Checking if current node is deletable
        if(!has_children(next_node)){
            delete next_node;
            node->children[child_index]=nullptr;
        }

    }else{
        //preventing substring from being deleted
        if(next_node->Lastchar==true){
            return;
        }
        //parent does not have children
        if(!has_children(next_node)){
            delete next_node;
            node->children[child_index]=nullptr;
        }
    }

}
//Helper function for detecting if given node has children
bool Trie::has_children(TrieNode* node){
    for(int i=0; i<26; ++i){
        if(node->children[i]!=nullptr){
            return true;
        }
    }
    return false;
}

//Printing words in trie in an alphabetic order
void Trie::Print(){
    if(num_words!=0){
        //Trie is not null, printing words
        std::string begin="";
        Print_helper(root,begin);
        std::cout<<std::endl;
    }
}
//Helper function for printing words
void Trie::Print_helper(TrieNode* node, std::string &word){
    //Looping through children
    for(int i=0; i<26; i++){
        if(node->children[i]!=nullptr){
            word.push_back(i+'A');
            //Reach the end of the word
            if(node->children[i]->Lastchar){
                //Printing the word
                std::cout<<word<<" ";
            }
            //Moving to the next node
            Print_helper(node->children[i],word);
            word.pop_back();
        }
    }
}

//Spell check function
void Trie::spellcheck(std::string word){
    TrieNode* curr = root;
    std::string prefixes="";
    //Checking if the given word is in the list
    for(int i=0; i<word.length();i++){
        int loc = word[i] -'A';
        prefixes.push_back(word[i]);
        //No match even from first letter
        if(i==0&&curr->children[loc]==nullptr){
            return;
        }

        //Prefix containing
        if(curr->children[loc]==nullptr){
            //Print the appropriate values
            prefixes.pop_back();
            if(curr->Lastchar){
                std::cout<<prefixes<<" ";
            }
            Print_helper(curr,prefixes);
            std::cout<<std::endl;
            return;
        }
        //Containing the word
        if((i==word.length()-1)&&(curr->children[loc]->Lastchar)){
            std::cout<<"correct"<<std::endl;
            return;
        }
        
        curr = curr->children[loc];
    }
    //Prefix containing (Edge case for single character escaping the conditions)
    if(curr->Lastchar){
        std::cout<<prefixes<<" ";
    }
        Print_helper(curr,prefixes);
            std::cout<<std::endl;
}

//Clear function for deleting all the words in the Trie
void Trie::clear(){
    TrieNode* curr = root;
    for(int i=0; i<26; i++){
        //Recursively deleting nodes except for the root
        if(curr->children[i]!=nullptr){
            TrieDestruct(curr->children[i]);
        }
    }
    num_words=0;
    std::cout<<"success"<<std::endl;
}

//Recursive function for deleting Trie
void Trie::TrieDestruct(TrieNode* node){
    for(int i=0; i<26; ++i){
        if(node->children[i] !=nullptr){
            //if there is a child, traverse down for further deletion
            TrieDestruct(node->children[i]);
        }
    }
    delete node;
}

//Checking if the Trie is empty function
void Trie::empty(){
    //checking number of words present
    if(num_words==0){
        Trie_Empty=true;
    }else{
        Trie_Empty=false;
    }
    if(Trie_Empty){
        std::cout<<"empty 1"<<std::endl;
    }else{
        std::cout<<"empty 0"<<std::endl;
    }
}

//Printing number of words in the Trie
void Trie::size(){
    std::cout<<"number of words is "<<num_words<<std::endl;
}

//Destructor for Trie
Trie::~Trie(){
    TrieDestruct(root);
}