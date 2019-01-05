#ifndef _STACK_H
#define _STACK_H

#include <cstddef>
#include <vector>

using namespace std;

class Stack {
public:
	Stack();
	Stack(int value);
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
private:
	struct Node {
		int data;
		Node* next;
		Node() {
			this->data = 0;
			this->next = NULL;
		}
		Node(int value) {
			this->data = value;
			this->next = NULL;
		}
	};
	Node* head_;
};

#endif
