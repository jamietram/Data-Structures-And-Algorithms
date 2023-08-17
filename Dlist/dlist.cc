#include <stdio.h> 
#include <stdlib.h>

#include "dlist.h"

// Constructor to initialize an empty list
DList::DList() {
	head = NULL;
	tail = NULL;
}

// Destructor to free memory used by the list
DList::~DList() {
	ListNode* curr = head;
	while (curr != NULL) {
		ListNode* temp = curr;
		curr = curr->next;
		delete temp;
	}
}

// Adds a new node with the given value to the front of the list
void DList::add_to_front(int value) {
    ListNode* new_node = new ListNode;
    new_node->val = value;
    new_node->next = head;
    new_node->prev = NULL;
    if (head != NULL) {
        head->prev = new_node;
    }
    head = new_node;
    if (tail == NULL) {
        tail = new_node;
    }
}

// Adds a new node with the given value to the back of the list
void DList::add_to_back(int value) {
	ListNode* new_node = new ListNode;
	new_node->val = value;
	new_node->next = NULL;
	new_node->prev = tail;
	if (tail == NULL) {
		head = new_node;
	} else {
		tail->next = new_node;
	}
	tail = new_node;
}

// Returns the value of the first node in the list
int DList::first() {
	if (head != NULL) {
		return head->val;
	} else {
		return -1; // Or some other default value
	}
}

// Returns the value of the last node in the list
int DList::last() {
	if (tail != NULL) {
		return tail->val;
	} else {
		return -1; // Or some other default value
	}
}

// Removes the given node from the list
void DList::remove(ListNode* node) {
	if (node == head) {
		head = node->next;
	} else {
		node->prev->next = node->next;
	}
	if (node == tail) {
		tail = node->prev;
	} else {
		node->next->prev = node->prev;
	}
	delete node;
}

// Returns a pointer to the node before the given node in the list
ListNode* DList::previous(ListNode* node) {
	return node->prev;
}

// Returns a pointer to the node after the given node in the list
ListNode* DList::next(ListNode* node) {
	return node->next;
}

// Searches the list for a node with the given value and returns a pointer to it
ListNode* DList::search_value(int value) {
	ListNode* curr = head;
	while (curr != NULL) {
		if (curr->val == value) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}