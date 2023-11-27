#include "Chaining.h"
#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "CubicProbing.h"
#include "Comp.h"
#include <cassert>

int i = 1;
void testDatabase(BaseClass *db) {
    db->createAccount("ABCD0000000_123456789", 1000);
    db->createAccount("ABCD0000000_123456987", 1500);
    db->createAccount("ABCD0000000_123456978", 2000);

    assert(db->getBalance("ABCD0000000_123456789") == 1000);
    assert(db->getBalance("ABCD0000000_123456987") == 1500);
    assert(db->getBalance("ABCD0000000_123456978") == 2000);

    db->addTransaction("ABCD0000000_123456789", -200);
    db->addTransaction("ABCD0000000_123456987", 300);
    db->addTransaction("ABCD0000000_123456978", -400);

    assert(db->getBalance("ABCD0000000_123456789") == 800);
    assert(db->getBalance("ABCD0000000_123456987") == 1800);
    assert(db->getBalance("ABCD0000000_123456978") == 1600);

    std::vector<int> topBalances = db->getTopK(2);
    assert(topBalances.size() == 2);
    assert(topBalances[0] == 1800);
    assert(topBalances[1] == 1600);

    assert(db->databaseSize() == 3);

    assert(db->doesExist("ABCD0000000_123456789"));
    cout << i++ << endl;
    assert(!db->doesExist("ABCD0000000_123459876"));
    
    cout << i++ << endl;
}
// 

int main() {
    Chaining chainingDB;
    LinearProbing linearProbingDB;
    QuadraticProbing quadraticProbingDB;
    CubicProbing cubicProbingDB;
    Comp compDB;

    std::cout << "Testing Chaining:" << std::endl;
    testDatabase(&chainingDB);

    std::cout << "\nTesting Linear Probing:" << std::endl;
    testDatabase(&linearProbingDB);

    std::cout << "\nTesting Comp:" << std::endl;
    testDatabase(&compDB);
    
    std::cout << "\nTesting Quadratic Probing:" << std::endl;
    testDatabase(&quadraticProbingDB);

    std::cout << "\nTesting Cubic Probing:" << std::endl;
    testDatabase(&cubicProbingDB);

    
    return 0;
}
