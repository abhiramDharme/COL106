#include "CubicProbing.h"
#define limit3 302429

int p3 = 1;

vector<int> sp3(limit3, 0);

int CubicProbing::hash(std::string id){
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
    return n%limit3;
}

void CubicProbing::createAccount(std::string id, int count){
    if(p3){
        int i = limit3;
        while(i--){
            Account A;
            A.balance = 0;
            A.id = "";
            bankStorage1d.push_back(A);
        }
        p3--;
    }
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l3 = static_cast<int64_t>(102503);
    while(i<l3 && sp3[(z+i*i*i)%l3]==1){
        i++;
    }
    z = (z+i*i*i)%l3;
    bankStorage1d[z].balance = count;
    bankStorage1d[z].id = id;
    sp3[z]++;
}

std::vector<int> CubicProbing::getTopK(int k){
    vector<int> top;
    for(int i=0; i<limit3; i++){
        if(sp3[i]){
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

int CubicProbing::getBalance(std::string id){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l3 = static_cast<int64_t>(102503);
    while(i<l3 && bankStorage1d[(z+i*i*i)%l3].id!=id){
        i++;
    }
    z = (z+i*i*i)%l3;
    if(bankStorage1d[z].id==id){
        return bankStorage1d[z].balance;
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l3 = static_cast<int64_t>(102503);
    while(i<l3 && bankStorage1d[(z+i*i*i)%l3].id!=id){
        i++;
    }
    z = (z+i*i*i)%l3;
    if(bankStorage1d[z].id==id){
        bankStorage1d[z].balance += count;
        return;
    }
    createAccount(id, count);
}

bool CubicProbing::doesExist(std::string id){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l3 = static_cast<int64_t>(102503);
    while(i<l3 && bankStorage1d[(z+i*i*i)%l3].id!=id){
        i++;
    }
    z = (z+i*i*i)%l3;
    return (bankStorage1d[z].id==id);
}

bool CubicProbing::deleteAccount(std::string id){
    int64_t z = hash(id);
    int64_t i = 0;
    int64_t l3 = static_cast<int64_t>(102503);
    while(i<l3 && bankStorage1d[(z+i*i*i)%l3].id!=id){
        i++;
    }
    z = (z+i*i*i)%l3;
    if(bankStorage1d[z].id==id){
        sp3[z]--;
        bankStorage1d[z].id = "";
        return true;
    }
    return false;
}

int CubicProbing::databaseSize(){
    int n = 0;
    for(int i=0; i<limit3; i++){
        n += sp3[i];
    }
    return n;
}