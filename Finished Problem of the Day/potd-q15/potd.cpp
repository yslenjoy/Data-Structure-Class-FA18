#include "potd.h"
#include <iostream>
#include <string>

using namespace std;

string stringList(Node *head) {
    // your code here!
    // string a = "Node " + to_string(count) + ": " + to_string(node->data_);
    string a = "";
    if (head == NULL) {
        return "Empty list";
    }

    int count = 0;
    Node * node = head;
    while (node != NULL) {
        // cout << "here111------: " << a << endl;
    	a = a + "Node " + to_string(count) + ": " + to_string(node->data_);
        // cout << "here222------: " << a << endl; 
        if (node->next_ != NULL) {
            a += " -> ";
        }
        count++;
        node = node->next_;
    }
    return a;
}
