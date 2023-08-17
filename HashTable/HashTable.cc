#include "HashTable.h"

HashTable::HashTable(int capacity) : nSlot(capacity), nElem(0), load(0.0)
{
    table = new int[nSlot];
    for (int i = 0; i < nSlot; i++)
        table[i] = -1;
}
void HashTable::clear()
{
    delete[] table;
    table = NULL;
    nSlot = 0;
    nElem = 0;
    load = 0.0;
}

HashTable::~HashTable()
{
    clear();
}


int HashTable::insert(int value)
{
    if (nElem == nSlot)
        return -1;

    int probes = 0;
    int index = hash(value);

    while (table[index] != -1)
    {
        probes++;
        index = (index + 1) % nSlot;
    }

    table[index] = value;
    nElem++;
    load = static_cast<double>(nElem) / nSlot;
    return probes;
}

bool HashTable::find(int value, int& nProbes)
{
    int index = hash(value);
    nProbes = 0;

    while (table[index] != -1)
    {
        nProbes++;
        if (table[index] == value)
            return true;
        index = (index + 1) % nSlot;
    }

    return false;
}

bool HashTable::is_full() const
{
    return nElem == nSlot;
}

int HashTable::hash(int value) const
{
    const double A = 0.6180339887;
    double fractionalPart = value * A - static_cast<int>(value * A);
    return static_cast<int>(nSlot * fractionalPart);
}