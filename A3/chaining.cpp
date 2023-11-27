#include "Chaining.h"
#define limit 10007

vector<int> len(limit, 0);

int p = 1;

int Chaining::hash(string id){
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
    return n%limit;
}

void Chaining::createAccount(std::string id, int count){
    if(p){
        for(int i=0; i<limit; i++){
            vector<Account> vec;
            bankStorage2d.push_back(vec);
        }
        p--;
    }
    int z = hash(id);
    Account A;
    A.balance = count;
    A.id = id;
    bankStorage2d[z].push_back(A);
    len[z]++;
}

vector<int> Chaining::getTopK(int k) {
    vector<int> top;
    for(int i=0; i<bankStorage2d.size(); i++){
        for(Account j : bankStorage2d[i]){
            top.push_back(j.balance);
        }
    }
    vector<int> TopK;
    int nn = top.size();
    int m = min(k,nn);
    for(int j=0; j<m; j++){
        int max = getMax(top);
        TopK.push_back(max);
    }
    top.clear();
    return TopK; // Placeholder return value
}

int Chaining::getBalance(std::string id){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            return bankStorage2d[z][i].balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count){
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
    len[z]++;
}

bool Chaining::doesExist(std::string id){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id){
    int z = hash(id);
    for(int i=0; i<bankStorage2d[z].size(); i++){
        if(bankStorage2d[z][i].id==id){
            bankStorage2d[z].erase(bankStorage2d[z].begin()+i);
            len[z]--;
            return true;
        }
    }
    return false; // Placeholder return value
}

int Chaining::databaseSize(){
    int sum = 0;
    for(int i=0; i<limit; i++){
        sum += len[i];
    }    
    return sum; // Placeholder return value
}
