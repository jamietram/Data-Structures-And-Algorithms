#include <iostream>
#include <cstdlib>
#include <ctime>
#include "HashTable.h"
#include "HashTable.cc"

int main()
{
    const int capacity = 10000;
    const double targetLoad1 = 0.5;
    const double targetLoad2 = 0.9;
    int reprobes1 = 0, reprobes2 = 0;
    int insertions1 = 0, insertions2 = 0;

    std::srand(static_cast<unsigned>(std::time(NULL)));

    // Hash table with target load factor 50%
    HashTable hashTable1(capacity);
    while (hashTable1.load_factor() < targetLoad1 && !hashTable1.is_full())
    {
        int randomNum = std::rand() % 100001;
        int reprobes = hashTable1.insert(randomNum);
        reprobes1 += reprobes; 
        insertions1++;
    }

    // Hash table with target load factor 90%
    HashTable hashTable2(capacity);
    while (hashTable2.load_factor() < targetLoad2 && !hashTable2.is_full())
    {
        int randomNum = std::rand() % 100001;
        int reprobes = hashTable2.insert(randomNum);
        reprobes2 += reprobes; 
        insertions2++;
    }

    double averageReprobes1 = static_cast<double>(reprobes1) / insertions1;
    double averageReprobes2 = static_cast<double>(reprobes2) / insertions2;

    std::cout << "50% full: " << averageReprobes1 << std::endl;
    std::cout << "90% full: " << averageReprobes2 << std::endl;

    return 0;
}
