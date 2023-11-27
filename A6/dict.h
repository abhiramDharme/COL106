// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#define len 54

struct node {
    char val = '☺';
    node* child[len] = {nullptr};
    int count = 0;

    node(){

    }

    node(char ch) {
        val = ch;
    }

    ~node(){
        val='☺';
        for(int i=0;i<len;i++){
            if(child[i]!=nullptr){
                delete child[i]; child[i]=nullptr;
            }
        }
        count=0;
    }
};

class Dict {
private:
    // You can add attributes/helper functions here
    node* root;

    void insert(string word);

    int fun(char ch){
        if(ch>='a' && ch<='z'){
            return ch-'a';
        }
        else if(ch>='A' && ch<='Z'){
            return ch-'A';
        }
        else if(ch>='0' && ch<='9'){
            return ch-22;
        }
        else{
            switch(ch){
                case '+':
                    return 36;
                case '*':
                    return 37;
                case '/':
                    return 38;
                case '&':
                    return 39;
                case '%':
                    return 40;
                case '#':
                    return 41;
                case '<':
                    return 42;
                case '=':
                    return 43;
                case '>':
                    return 44;
                case '$':
                    return 45;
                case '^':
                    return 46;
                case '_':
                    return 47;
                case '\\':
                    return 48;
                case '`':
                    return 49;
                case '~':
                    return 50;
                case '{':
                    return 51;
                case '}':
                    return 52;
                case '|':
                    return 53;
            }
        }
    }

    bool isSpecialCharacter(char ch) {
    switch (ch) {
        case ' ':
        case '.':
        case ',':
        case '-':
        case ':':
        case '!':
        case '"':
        case '\'':
        case '(':
        case ')':
        case '?':
        case '[':
        case ']':
        case ';':
        case '@':
            return true;
        default:
            return false;
    }
}

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
