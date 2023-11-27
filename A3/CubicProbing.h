#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
using namespace std;

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // Other data members and functions specific to Quadratic Probing

    int getMax(vector<int> &top){
        int n = top.size();
        int max = top[0];
        int j = 0;
        for(int i=1; i<n; i++){
            if(max<top[i]){
                max = top[i];
                j = i;
            }
        }
        top[j] = -1;
        return max;
    }

};

#endif // CUBICPROBING_H
