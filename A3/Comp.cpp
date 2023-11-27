#include "Comp.h"
#define limit4 10007

vector<int> len1(limit4, 0);

int q = 1;

int Comp::hash(string id){
    int n1 = id[0];
    int n2 = id[1];
    int n3 = id[2];
    int n4 = id[3];
    string a = id.substr(17,5);
    string b = id.substr(12,5);
    string c = id.substr(4,3);
    string d = id.substr(7,3);
    int n = 2*stoi(a);
    n += 3*stoi(b);
    n += 5*stoi(c);
    n += 7*stoi(d);
    n += 11*n1*n1;
    n += 13*n2*n2;
    n += 17*n3*n3;
    n += 19*n4*n4;
    return n%limit4;
}

void Comp::createAccount(std::string id, int count){
    if(q){
        for(int i=0; i<limit4; i++){
            vector<Account> vec;
            bankStorage2d.push_back(vec);
        }
        q--;
    }
    int z = hash(id);
    Account A;
    A.balance = count;
    A.id = id;
    bankStorage2d[z].push_back(A);
    len1[z]++;
}

vector<int> Comp::getTopK(int k) {
    vector<int> top;
    for(int i=0; i<bankStorage2d.size(); i++){
        for(Account j : bankStorage2d[i]){
            top.push_back(j.balance);
        }
    }
    vector<int> TopK;
    int nn = top.size();
    k = min(k,nn);
    for(int j=0; j<k; j++){
        int max = getMax(top);
        TopK.push_back(max);
    }
    return TopK; // Placeholder return value
}

int Comp::getBalance(std::string id){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            return bankStorage2d[z][i].balance;
        }
    }
    return -1;
}

void Comp::addTransaction(std::string id, int count){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            bankStorage2d[z][i].balance += count;
            return;
        }
    } 
    Account A;
    A.balance = count;
    A.id = id;
    bankStorage2d[z].push_back(A);
}

bool Comp::doesExist(std::string id){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            bankStorage2d[z].erase(bankStorage2d[z].begin()+i);
            len1[z]--;
            return true;
        }
    }
    return false; // Placeholder return value
}

int Comp::databaseSize(){
    int sum = 0;
    for(int i=0; i<limit4; i++){
        sum += len1[i];
    }    
    return sum; // Placeholder return value
}