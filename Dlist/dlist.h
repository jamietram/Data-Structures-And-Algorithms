#ifndef DLIST_H
#define DLIST_H

struct ListNode 
{
  /* define your list node type */
  int val;
  ListNode* next;
  ListNode* prev;
};

class DList
{
  public:
  DList();
  /* implement copy constructor, assignment, destructor if needed */
  DList(const DList& other); // copy constructor
  DList& operator=(const DList& other); // assignment operator
  ~DList();

  void add_to_front(int value);
  void add_to_back(int value);
  int first();
  int last();
  void remove(ListNode* node);
  ListNode* previous(ListNode* node);
  ListNode* next(ListNode* node);
  ListNode* search_value(int value);

  private:
  /* declare your data */
  ListNode* head;
  ListNode* tail;
};

#endif
