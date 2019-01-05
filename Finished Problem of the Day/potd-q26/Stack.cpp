#include "Stack.h"
#include <vector>
#include <iostream>

using namespace std;

Stack::Stack() {
	this->head_ = NULL;
  // this->head_ = new Node(); ***** THIS IS WRONG ****, head would never be NULL then
}

Stack::Stack(int value) {
	this->head_ = new Node(value);
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Stack::size() const {
  if (head_ == NULL) {
  	return 0;
  }
  int count = 0;
  Node* cur = head_;
  while (cur != NULL) {
  	count += 1;
  	cur = cur->next;
  }
  return count;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
  return head_ == NULL;
  // if (this->size() == 0) {
  // 	return true;
  // } else {
  // 	return false;
  // }
}

// `void push(int val)` - pushes an item to the stack in O(1) time
void Stack::push(int value) {
		Node* node = new Node(value);
		node->next = head_;
		head_ = node;
}

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
	Node* del = head_;
	int value = del->data;
	head_ = del->next;
	del->next = NULL;
	delete del;
	del = NULL;
	return value;
}
