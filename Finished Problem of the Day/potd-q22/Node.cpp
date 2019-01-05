#include "Node.h"
#include <iostream>

using namespace std;


Node* removeDuplicates(Node* head) {
	if (head == NULL) {
		return NULL;
	}
	Node *ptr1, *ptr2, *dup;
	ptr1 = head;
	while (ptr1 != NULL && ptr1->next_!= NULL) {
	  ptr2 = ptr1;
	  while (ptr2->next_ != NULL) {
	    if (ptr1->data_ == ptr2->next_->data_) {
	      dup = ptr2->next_;
	      ptr2->next_ = ptr2->next_->next_;
	      dup->next_ = NULL;
	      // delete dup;
	    } else {
	      ptr2 = ptr2->next_;
	    }
	  }
	  ptr1 = ptr1->next_;
	}
	return head;
}

bool isPresent(Node *head, int data) {
  Node* t = head;
  while (t != NULL) {
    if (t->data_ == data) {
      return true;
    }
    t = t->next_;
  }
  // cout << "here3----" << endl;
  return false;
}


Node *listIntersection(Node *first, Node *second) {
  // your code here
	if (first==NULL || second==NULL){
		return NULL;
	}
	Node* first1 = removeDuplicates(first);
	Node* second1 = removeDuplicates(second);
	// Remove function works fine after testing
	// cout << "first1------" << endl; 
	// Node *temp = first1;
	// int count = 0;
	// while(temp != NULL) {
	//   cout << "Node " << count << ": " << temp ->data_ << endl;
	//   count++;
	//   temp = temp->next_;
	// }

	Node* intersection = new Node;
	Node* head = intersection;
	int countI = 0;
	// Node* next = *Node();
	// cout << "----------" << endl;
	while (second1 != NULL) {
		if (isPresent(first1, second1->data_)) {
			countI++;
			if (countI == 1) {
				intersection->data_ = second1->data_;
				intersection->next_ = NULL; // *** cannot missing
			} else {
				// cout << "count2: "<< countI << endl;
				Node* next = new Node();
				next->data_ = second1->data_;
				// cout << "next data: " << next->data_ << endl;
				next->next_ = NULL;
				intersection ->next_ = next;	
				intersection = next;
			}
		}
		second1 = second1->next_;
	}
	if (countI == 0) {
		intersection->~Node(); // *** cannot missing
		return NULL;
	}
	// cout << "count: "<< countI << endl;
	return head;
}


Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
