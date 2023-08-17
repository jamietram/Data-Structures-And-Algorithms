#ifndef HASHTABLE_H
#define HASHTABLE_H

class HashTable
{
  public:
  HashTable (int capacity);
  /* implement copy constructor, assignment, destructor if needed */
   ~HashTable();

  int insert (int value); 
  /* insert the input value and return the number of probes
   * return -1 if the table is full and insert fails */

  bool find (int value, int& nProbes);  
  /* Search for the input value in table
   * Return true if the search is successful, otherwise false
   * Save # probes in 'nProbes' */

  // getters
  int capacity() { return nSlot; }
  int size() { return nElem; }
  double load_factor() { return load; }
  
  // New function to check if the table is full
  bool is_full() const;

  private:
  /* declare your data */
  int* table;
  double load;     // track the load factor of table
  int    nSlot;    // # slots i.e. max # elements can hold 
  int    nElem;    // current # elements in table

  int hash(int value) const;
  void clear();
};


#endif
