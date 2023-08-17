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
    const int numSearches = 10000;
    int reprobes1 = 0, reprobes2 = 0;

    std::srand(static_cast<unsigned>(std::time(NULL)));

    // Hash table with target load factor 50%
    HashTable hashTable1(capacity);
    while (hashTable1.load_factor() < targetLoad1)
    {
        int randomNum = std::rand() % 100001;
        hashTable1.insert(randomNum);
    }

    // Hash table with target load factor 90%
    HashTable hashTable2(capacity);
    while (hashTable2.load_factor() < targetLoad2)
    {
        int randomNum = std::rand() % 100001;
        hashTable2.insert(randomNum);
    }

    // Measure average number of reprobes for search operations
    for (int i = 0; i < numSearches; ++i)
    {
        // Generate a random number to search for
        int randomNum = std::rand() % 100001;

        // Search in the hash table with 50% load factor
        int nProbes;
        hashTable1.find(randomNum, nProbes);
        reprobes1 += nProbes;

        // Search in the hash table with 90% load factor
        hashTable2.find(randomNum, nProbes);
        reprobes2 += nProbes;
    }

    double averageReprobes1 = static_cast<double>(reprobes1) / numSearches;
    double averageReprobes2 = static_cast<double>(reprobes2) / numSearches;

    std::cout << "50% full: " << averageReprobes1 << std::endl;
    std::cout << "90% full: " << averageReprobes2 << std::endl;

    return 0;
}