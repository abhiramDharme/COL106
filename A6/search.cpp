// Do NOT add any other includes
#include "search.h"
SearchEngine::SearchEngine(){
    // Implement your function here
    
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
    for (int i=0; i<vec.size(); i++) {
        delete vec[i];
        vec[i] = nullptr;
    }
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    obj* temp = new obj();
    temp->book_code = book_code;
    temp->page = page;
    temp->paragraph = paragraph;
    string sent = "";
    for(int i=0;i<sentence.length();i++){
        char ch = sentence[i];
        if(ch>='A' && ch<='Z'){
            sent+= ch +32;
        }
        else{
            sent+=ch;
        }
    }
    temp->sentence = sent;
    temp->sentence_no = sentence_no;
    vec.push_back(temp);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here
    n_matches = 0;
    int n = pattern.size();
    string mypattern = "";
    for(int i=0;i<pattern.length();i++){
        char ch = pattern[i];
        if(ch>='A' && ch<='Z'){
            mypattern+= ch +32;
        }
        else{
            mypattern+=ch;
        }
    }

    Node* head = nullptr;
    Node* ans = nullptr;
    int value = Hash(mypattern, n);
    
    for (int k = 0; k<vec.size(); k++) {
        int m = vec[k]->sentence.size();
        if(n>m){continue;}

        int i = 0; int j = n-1;
        int hash = Hash(vec[k]->sentence, n);
        if ((value == hash) && (mypattern == vec[k]->sentence.substr(0, n)) ) {
            Node* newNode = new Node(vec[k]->book_code, vec[k]->page, vec[k]->paragraph, vec[k]->sentence_no, i);
            if(head==nullptr){
                head = newNode; ans = head;
            }
            else{
                head->right = newNode; newNode->left = head;
                head = head->right;
            }
            n_matches++;
        }
        
        while (j<m-1) {
            j++;
            hash = updateHash(hash, vec[k]->sentence[i], vec[k]->sentence[j], n);
            i++;
            if ((value == hash) && (mypattern == vec[k]->sentence.substr(i, n)) ) {
                Node* newNode = new Node(vec[k]->book_code, vec[k]->page, vec[k]->paragraph, vec[k]->sentence_no, i);
                if(head==nullptr){
                    head = newNode; ans = head;
                }
                else{
                    head->right = newNode; newNode->left = head;
                    head = head->right;
                }
                n_matches++;
                
            }
            
        }
        
    }
    if (!n_matches) return nullptr;
    return ans;
}
