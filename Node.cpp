#include <vector>
#include <iostream>

class Node{

    std::vector<Node*> children;
    Node* parent;
    char letter;
    bool term;

    public:

    Node( char l, Node* par ){
        children = std::vector<Node*>(26);
        parent = par;
        letter = l;
        term = false;
    }

    char getLetter(){
        return letter;
    }

    bool getTerm(){
        return term;
    }

    void setTerm( bool t ){
        term = t;
    }

    Node* getParent(){
        return parent;
    }

    Node* getCharSubtree( char l ){
        return children[ int(l) - 65 ];
    }

    void setCharSubtree( Node* n ){
        children[ int(n->getLetter()) - 65 ] = n;
    }

    void deleteCharSubtree( char l ){
        Node* del = getCharSubtree(l);
        children[ int(l) - 65 ] = nullptr;
        delete del;
        del = nullptr;
    }

    void prefix( unsigned int& count ){
        count += term;
        for (int i = 0; i < 26; ++i){
            if (children[i]){
                children[i]->prefix(count);
            }
        }
    }

    unsigned int numChildren(){
        unsigned int count = 0;
        for (int i = 0; i < 26; ++i){
            if (children[i]){
                ++count;
            }
        }
        return count;
    }

    void printWord(Node* n){
        std::string word = "";
        while (n){
            word = n->getLetter() + word;
            n = n->getParent();
        }
        std::cout << word << " ";
    }

    void alphabeticalWalk(){
        if (term){
            printWord(this);
        }
        for (int i = 0; i < 26; ++i){
            if (children[i]){
                children[i]->alphabeticalWalk();
            }
        }
    }

    void deleteSubtree(){
        for (int i = 0; i < 26; ++i){
            if (children[i]){
                children[i]->deleteSubtree();
                children[i] = nullptr;
            }
        }
        delete this;
    }

};