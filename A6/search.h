// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
#define MOD 10007
#define BASE 97

struct obj {
    public:
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    string sentence;

    obj(){
        
    }

    ~obj(){
        
    }
};

class SearchEngine {
private:
    // You can add attributes/helper functions here
    vector<obj*> vec;

    int Hash(string str, int length) {
        int hash = 0;
        for (int i = 0; i < length; ++i) {
            hash = (hash * BASE + str[i]) % MOD;
        }
        return hash;
    }

    int modPow(int base, int exp, int mod) {
        int result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }

    int updateHash(int oldHash, char oldChar, char newChar, int length) {
        int newHash = (oldHash - oldChar * modPow(BASE, length - 1, MOD)) * BASE + newChar;
        newHash = (newHash % MOD + MOD) % MOD;
        return newHash;
    }

public:
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};
