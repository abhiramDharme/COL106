// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
    root = new node();
}

Dict::~Dict(){
    // Implement your function here
    delete root;  root = nullptr;
}

void Dict::insert(string word){
    node* temp = root;

    for (int i=0; i<word.length(); i++){
        int index = fun(word[i]);

        if(temp->child[index] == nullptr){
            temp->child[index] = new node(word[i]);
            temp = temp->child[index];
        }
        else{
            temp = temp->child[index];
        }
    }
    
    temp->count++;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    string word = "";
    
    for(int i=0;i<sentence.length();i++){
        char ch = sentence[i];
        if(ch>='A' && ch<='Z'){
            ch = ch+32;
            word = word+ch;
        }
        //seperators   . , - : ! " ' ( ) ? [ ] ; @
        else if(isSpecialCharacter(ch)){
            if(word!=""){
                insert(word); 
                word="";
            }
        }
        else{
            word = word+ch;
        }
    }
    
    if(word!=""){
        insert(word); 
        word="";
    }
    
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here
    node* temp = root;
    for (int i=0; i<word.size(); i++) {
        if (temp->child[fun(word[i])] == nullptr) {
            return 0;
        }
        temp = temp->child[fun(word[i])];
    }
    return temp->count;
}

void parse(string s, ofstream &filename, node* temp){
    s += temp->val;

    if(temp->count > 0){
        filename << s << ", " << temp->count << "\n";
    }

    for(int i=0;i<len;i++){
        if(temp->child[i]!=nullptr){
            parse(s, filename, temp->child[i]);
        }
    }

    return;
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    string s = "";
    ofstream file(filename);
    for(int i=0;i<len;i++){
        if(root->child[i]!=nullptr){
            parse(s, file, root->child[i]);
        }
    }

    return;
}
