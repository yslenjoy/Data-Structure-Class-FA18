#include <vector>
#include "BTreeNode.h"


BTreeNode* find(BTreeNode* root, int key) {
   // Your Code Here
  
  if (root == NULL) {
  	return NULL;
  }
  for (int i = 0; i < root->elements_.size(); i++) {
  	if (root->elements_[i] == key) {
  		return root;
  	}
  }
  for (int j = 0; j < root->children_.size(); j++) {
  	if (find(root->children_[j], key) != NULL) {
  		return find(root->children_[j], key);
  	}
  }
  return NULL;
}
