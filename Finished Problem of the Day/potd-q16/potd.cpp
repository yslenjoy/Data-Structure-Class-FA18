#include "potd.h"
#include <iostream>

using namespace std;

void insertSorted(Node **head, Node *insert) {
  // your code here!
  Node * tmp = *head;

  while(tmp != NULL && tmp->data_ < insert->data_) {
    head = &tmp->next_;
    tmp = tmp->next_;
  }
  *head = insert;
  insert->next_ = tmp;
  //empty case
  // if (*head == NULL) {
  // 	// cout<<"*head NULL-------" <<endl;
  // 	insert->next_ = *head;
  // 	*head = insert;
  // } 

  // // only one element
  // if ((*head)->next_ == NULL && (*head)->data_ < insert->data_) {
  // 	(*head)->next_ = insert;
  // 	// return;
  // }
  // if ((*head)->next_ == NULL && (*head)->data_ >= insert->data_) {
  // 	insert = (*head)->next_;
  // 	// return;
  // }

  // // more than one element
  // if ((*head)->data_ < insert->data_) {
  // 	insert->next_ = *head;
  // 	*head = insert;
  // 	// insertSorted(Node **head, Node *insert);
  // } else {
  // 	insert = (*head)->next_;
  // }
}
