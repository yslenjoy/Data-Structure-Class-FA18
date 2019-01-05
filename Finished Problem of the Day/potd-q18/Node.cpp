#include "Node.h"

using namespace std;

void mergeList(Node *first, Node *second) {
  // your code here!
  while (first !=NULL) {
  	if (second ==NULL || first == NULL) {
  		return;
  	}
  	Node * tmp1 = first->next_;
  	Node * tmp2 = second->next_;
  	first->next_ = second;
  	if (tmp1 == NULL) {
  		return;
  	}
  	second->next_ = tmp1;
  	first = tmp1;
  	second = tmp2;
  }
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

