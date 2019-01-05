#include "Node.h"

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

Node *listSymmetricDifference(Node *first, Node *second) {
  // your code here
  if (first == NULL && second == NULL) {
    // Node * listSD = new Node;
    // listSD = NULL;
    return NULL;
  }
  if (first == NULL) {
    Node * listSD = new Node(*second);
    // listSD->~Node();
    return listSD;
  }
  if (second == NULL) {
    Node * listSD = new Node(*first);
    // listSD->~Node();
    return listSD;
  }

  Node* first1 = removeDuplicates(first);
  Node* second1 = removeDuplicates(second);
  Node* h1 = first1;
  Node* h2 = second1;

  Node* listSD = new Node;
	Node* head = listSD;
  int countI = 0;

  while (h2 != NULL) {
  	if (!isPresent(first1, h2->data_)) {
  		countI++;
  		if (countI == 1) {
  			listSD->data_ = h2->data_;
  			listSD->next_ = NULL;
  		} else {
  			Node* next1 = new Node();
  			next1 -> data_ = h2->data_;
  			next1->next_ = head;
  			head = next1;
  		}
  	}
  	h2 = h2->next_;
  }

  while (h1 != NULL) {
  	if (!isPresent(second1, h1->data_)) {
  		countI++;
  		if (countI == 1) {
  			listSD->data_ = h1->data_;
  			listSD->next_ = NULL;
  		} else {
  			Node* next2 = new Node();
  			next2 -> data_ = h1->data_;
  			next2->next_ = head;
  			head = next2;
  		}
  	}
  	h1 = h1->next_;
  }

  if (countI == 0) {
		listSD->~Node(); // *** cannot missing
		return NULL;
	}

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
