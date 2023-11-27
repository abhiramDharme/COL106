#include "LinearProbing.h"
#define limit1 100000

int p1 = 1;

vector<int> sp1(limit1, 0);

int LinearProbing::hash(std::string id){
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
    return n%limit1;
}

void LinearProbing::createAccount(std::string id, int count){
    if(p1){
        int i = limit1;
        while(i--){
            Account A;
            A.balance = 0;
            A.id = "";
            bankStorage1d.push_back(A);
        }
        p1--;
    }
    int z = hash(id);
    while(sp1[(z)%limit1]){
        z++;
    }
    z = z%limit1;
    bankStorage1d[z].balance = count;
    bankStorage1d[z].id = id;
    sp1[z]++;

}

vector<int> LinearProbing::getTopK(int k){
    vector<int> top;
    for(int i=0; i<limit1; i++){
        if(sp1[i]){
            top.push_back(bankStorage1d[i].balance);
        }
    }
    int nn = top.size();
    k = min(k,nn);
    vector<int> vec(k);
    for(int j=0; j<k; j++){
        int max = getMax(top);
        vec[j] = max;
    }
    return vec;
}

int LinearProbing::getBalance(std::string id){
    int z = hash(id);
    int i = 0;
    while(i<limit1 && bankStorage1d[z%limit1].id!=id){
        z++; i++;
    }
    z = z%limit1;
    if(bankStorage1d[z].id==id){
        return bankStorage1d[z].balance;
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count){
    int z = hash(id);
    int i = 0;
    while(i<limit1 && bankStorage1d[z%limit1].id!=id){
        z++; i++;
    }
    z = z%limit1;
    if(bankStorage1d[z].id==id){
        bankStorage1d[z].balance += count;
        return;
    }
    createAccount(id, count);
}

bool LinearProbing::doesExist(std::string id){
    int z = hash(id);
    int i = 0;
    while(i<limit1 && bankStorage1d[z%limit1].id!=id){
        z++; i++;
    }
    z = z%limit1;
    return (bankStorage1d[z].id==id);
}

bool LinearProbing::deleteAccount(std::string id){
    int z = hash(id);
    int i = 0;
    while(i<limit1 && bankStorage1d[z%limit1].id!=id){
        z++; i++;
    }
    z = z%limit1;
    if(bankStorage1d[z].id==id){
        sp1[z]--;
        bankStorage1d[z].id = "";
        return true;
    }
    return false;
}

int LinearProbing::databaseSize(){
    int n = 0;
    for(int i=0; i<limit1; i++){
        n += sp1[i];
    }
    return n;
}