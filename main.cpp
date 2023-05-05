#include <iostream>
#include <fstream>
#include "Trie.cpp"

using namespace std;

int main(){

    Trie* t = new Trie();
    string cmd;

    while (cin >> cmd){

        if (cmd == "load"){

            ifstream fin("corpus.txt");
            string word;

            while (fin >> word){
                t->addWord(word);
            }

            cout << "success" << endl;

        }

        else if (cmd == "i"){
            
            string word;
            cin >> word;

            int successCode = t->addWord(word);

            if (successCode == 1){
                cout << "success" << endl;
            }
            else if (successCode == 0){
                cout << "failure" << endl;
            }

        }

        else if (cmd == "c"){

            string pre;
            cin >> pre;

            int count = t->prefix(pre);

            if (count > 0){
                cout << "count is " << count << endl;
            }
            else if (!count){
                cout << "not found" << endl;
            }

        }

        else if (cmd == "e"){

            string word;
            cin >> word;

            int successCode = t->deleteWord(word);

            if (successCode == 1){
                cout << "success" << endl;
            }
            else if (successCode == 0){
                cout << "failure" << endl;
            }

        }

        else if (cmd == "p"){

            t->print();
            if (t->getSize()){
                cout << endl;
            }

        }

        else if (cmd == "spellcheck"){

            string word;
            cin >> word;

            if (t->spellcheck(word)){
                cout << "correct";
            }

            cout << endl;

        }

        else if (cmd == "empty"){

            if (t->empty()){
                cout << "empty 1" << endl;
            }
            else{
                cout << "empty 0" << endl;
            }

        }

        else if (cmd == "clear"){

            t->clearTrie();
            cout << "success" << endl;

        }

        else if (cmd == "size"){

            cout << "number of words is " << t->getSize() << endl;

        }

        else{
            break;
        }

    }

    delete t;
    t = nullptr;

    return 0;
}