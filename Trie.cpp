#include <iostream>
#include "Node.cpp"
#include "illegal_exception.cpp"

using namespace std;

class Trie{

    Node* root;
    unsigned int numWords;
    void checkInput( string s ){
        for (int i = 0; i < s.length(); ++i){
            if ((int(s[i]) > 90) || (int(s[i]) < 65)){
                throw illegal_exception();
                break;
            }
        }
    }

    public:

    Trie(){
        root = new Node(0, nullptr);
        numWords = 0;
    }

    ~Trie(){
        root->deleteSubtree();
    }

    int addWord( string word ){
        try{
            checkInput(word);
        }
        catch(illegal_exception x){
            cout << x.message << endl;
            return -1;
        }

        if (root->getCharSubtree(word[0]) == nullptr){
            Node* prev = new Node(word[0], root);
            root->setCharSubtree(prev);
            for (int i = 1; i < word.length(); ++i){
                Node* curr = new Node(word[i], prev);
                prev->setCharSubtree(curr);
                prev = curr;
            }
            prev->setTerm(true);
        }
        else{
            Node* prev = root->getCharSubtree(word[0]);
            int iter = 1;
            for (int i = 1; i < word.length(); ++i){
                Node* curr = prev->getCharSubtree(word[i]);
                if (!curr){
                    iter = i;
                    break;
                }
                prev = curr;
                ++iter;
            }
            for (int i = iter; i < word.length(); ++i){
                Node* curr = new Node(word[i], prev);
                prev->setCharSubtree(curr);
                prev = curr;
            }
            if (prev->getTerm()){
                return 0;
            }
            prev->setTerm(true);
        }
        ++numWords;
        return 1;
    }

    int prefix( string s ){
        try{
            checkInput(s);
        }
        catch(illegal_exception x){
            cout << x.message << endl;
            return -1;
        }

        unsigned int count = 0;
        Node* n = root;

        for (int i = 0; i < s.length(); ++i){
            n = n->getCharSubtree(s[i]);
            if (!n){
                return 0;
            }
        }

        n->prefix(count);
        return count;
    }

    bool empty(){
        return numWords == 0;
    }

    int deleteWord( string s ){
        try{
            checkInput(s);
        }
        catch(illegal_exception x){
            cout << x.message << endl;
            return -1;
        }

        Node* iter = root;
        for (int i = 0; i < s.length(); ++i){
            if (!iter->getCharSubtree(s[i])){
                return 0;
            }
            iter = iter->getCharSubtree(s[i]);
        }
        if (iter->numChildren()){
            iter->setTerm(false);
            --numWords;
            return 1;
        }
        else{
            Node* par = iter->getParent();
            while (par && par->numChildren() == 1){
                par->deleteCharSubtree(iter->getLetter());
                iter = par;
                par = iter->getParent();
            }
            if (par->numChildren() > 1){
                par->deleteCharSubtree(iter->getLetter());
            }
            --numWords;
            return 1;
        }
    }

    void print(){
        root->alphabeticalWalk();
    }

    bool spellcheck( string s ){
        Node* prev = root;
        if (!root->getCharSubtree(s[0])){
            return false;
        }
        for (int i = 0; i < s.length(); ++i){
            Node* curr = prev->getCharSubtree(s[i]);
            if (curr){
                prev = curr;
            }
            else{
                prev->alphabeticalWalk();
                return false;
            }
        }
        if (prev->getTerm()) return true;
        prev->alphabeticalWalk();
        return false;
    }

    void clearTrie(){
        if (!empty()){
            root->deleteSubtree();
            root = new Node(0, nullptr);
            numWords = 0;
        }
    }

    unsigned int getSize(){
        return numWords;
    }
    
};