#include <string>
// define your classes here...
class Trie{
    class TrieNode{
        public: 
            TrieNode* children[26];
            bool Lastchar;
            //Trie Node Constructor
            TrieNode();
    };
    private: 
        TrieNode* root;
        bool Trie_Empty;
        int num_words;
        //Recursive function to deleting Trie
        void TrieDestruct(TrieNode* node);
        //Helper function to calculate number of words with prefixes
        int countPrefix(TrieNode* node);
        //Helper function to erase word
        void Erase_helper(TrieNode* node, std::size_t index, const std::string &word);
        //Helper function for detecting if given node has a children
        bool has_children(TrieNode* node);
        //Helper function for detecting if the given node is end of another word
        bool End_another(TrieNode* node);
        //Helper function for printing
        void Print_helper(TrieNode* node, std::string &word);


    public:
        //Trie Constructor
        Trie();
        //Load Function
        void Load();
        //Insert function
        void Insert(std::string word, bool display);

        //Prefix Calculating Function
        void Prefix(std::string prefix);

        //Erasing word function
        void Erase(std::string word);

        //Printing all words in a trie function in an alphabetic order
        void Print();

        //Spell Check Function
        void spellcheck(std::string word);

        //Trie emptiness check function
        void empty();

        //Deleting all word function from Trie
        void clear();

        //Printing number of words in the Trie
        void size();

        //Trie Destructor
        ~Trie();

};