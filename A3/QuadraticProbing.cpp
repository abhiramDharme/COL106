#include "QuadraticProbing.h"
#define limit2 201031

int p2 = 1;

vector<int> sp2(limit2, 0);

int QuadraticProbing::hash(std::string id){
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
    return n%limit2;
}

void QuadraticProbing::createAccount(std::string id, int count){
    if(p2){
        int i = limit2;
        while(i--){
            Account A;
            A.balance = 0;
            A.id = "";
            bankStorage1d.push_back(A);
        }
        p2--;
    }
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l2 = static_cast<int64_t>(201031);
    while(i<l2 && sp2[(z+i*i)%l2]==1){
        i++;
    }
    z = (z+i*i)%l2;
    bankStorage1d[z].balance = count;
    bankStorage1d[z].id = id;
    sp2[z]++;
}

std::vector<int> QuadraticProbing::getTopK(int k){
    vector<int> top;
    for(int i=0; i<limit2; i++){
        if(sp2[i]){
            top.push_back(bankStorage1d[i].balance);
        }
    }
    int nn = top.size();
    int m = min(k,nn);
    vector<int> vec(m);
    for(int j=0; j<m; j++){
        int max = getMax(top);
        vec[j] = max;
    }
    top.clear();
    return vec;
}

int QuadraticProbing::getBalance(std::string id){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l2 = static_cast<int64_t>(201031);
    while(i<l2 && bankStorage1d[(z+i*i)%l2].id!=id){
        i++;
    }
    z = (z+i*i)%l2;
    if(bankStorage1d[z].id==id){
        return bankStorage1d[z].balance;
    }
    return -1;
}

void QuadraticProbing::addTransaction(std::string id, int count){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l2 = static_cast<int64_t>(201031);
    while(i<l2 && bankStorage1d[(z+i*i)%l2].id!=id){
        i++;
    }
    z = (z+i*i)%l2;
    if(bankStorage1d[z].id==id){
        bankStorage1d[z].balance += count;
        return;
    }
    createAccount(id, count);
}

bool QuadraticProbing::doesExist(std::string id){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l2 = static_cast<int64_t>(201031);
    while(i<l2 && bankStorage1d[(z+i*i)%l2].id!=id){
        i++;
    }
    z = (z+i*i)%l2;
    return (bankStorage1d[z].id==id);
}

bool QuadraticProbing::deleteAccount(std::string id){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l2 = static_cast<int64_t>(201031);
    while(i<l2 && bankStorage1d[(z+i*i)%l2].id!=id){
        i++;
    }
    z = (z+i*i)%l2;
    if(bankStorage1d[z].id==id){
        sp2[z]--;
        bankStorage1d[z].id = "";
        return true;
    }
    return false;
}

int QuadraticProbing::databaseSize(){
    int n = 0;
    for(int i=0; i<limit2; i++){
        n += sp2[i];
    }
    return n;
}