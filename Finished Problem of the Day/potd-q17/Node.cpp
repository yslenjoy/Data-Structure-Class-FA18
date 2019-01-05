#include "Node.h"
#include <iostream>

using namespace std;

void sortList(Node **head) {
  // your code here!
  // Node * prev;
  // Node * cur = *head;
  // while (cur != NULL) {
  //   prev = cur;
  //   cur = cur->next_;
  //   while (prev->data_ > cur->data_) {
  //     prev->next_ = cur->next_;
  //     cur->next_ = prev;

  //   }

  // }
    
  
  Node * newHead = NULL;
  Node * curHead = *head;
  Node * insert;
  while (curHead != NULL) {
    // cout << "here1----" << endl;
  	insert = curHead;
  	curHead = curHead->next_;
  	insert->next_ = NULL;
  	insertSorted(&newHead, insert);
    // cout << "here1: curHead---" << endl;
    // cout << "Node " << curHead->getNumNodes() << ": " << curHead ->data_ << endl;
    // Node * tmp = newHead;
    // while(tmp != NULL && tmp->data_ < insert->data_) {
    //   cout << "here2: tmp---" << endl;
    //   cout << "Node " << tmp->getNumNodes() << ": " << tmp ->data_ << endl;
    //   newHead = tmp->next_;
    //   tmp = tmp->next_;
    // }
    // newHead = insert;
    // insert->next_ = tmp;
    
  }
  *head = newHead;
}
void insertSorted(Node **head, Node * insert) {
  Node * tmp = *head;
  while(tmp != NULL && tmp->data_ < insert->data_) {
    head = &tmp->next_;
    tmp = tmp->next_;
  }
  *head = insert;
  insert->next_ = tmp;
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

