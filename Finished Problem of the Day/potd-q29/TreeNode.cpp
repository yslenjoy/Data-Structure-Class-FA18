#include "TreeNode.h"
#include <iostream>

using namespace std;

TreeNode*& _find(TreeNode*& root, const int key) {
  if (root == NULL || root->val_ == key) {
    return root;
  }
  if (key < root->val_) {
    return _find(root->left_, key);
  } 
  if (key > root->val_) {
    return _find(root->right_, key);
  }
}

TreeNode * deleteNode(TreeNode* root, int key) {
  // your code here
  if (root == NULL) {
    return NULL;
  }
  TreeNode*& node1 = _find(root, key);
  // cout << "here3-----: " << node1->val_ << endl;

  // leaf node remove
  if (node1->left_ == NULL && node1->right_ == NULL) {
    // cout << "here2---" << endl;
    delete node1;
    node1 = NULL;
    return root;
  }

  // one child (left) remove
  if (node1->left_ != NULL && node1->right_ == NULL) {
    TreeNode* tmp = node1;
    node1 = node1->left_;
    delete tmp;
    return root;
  }

  // One-child (rihgt) remove
  if (node1->left_ == NULL && node1->right_ != NULL) {
    TreeNode* tmp = node1;
    node1 = node1->right_;
    delete tmp;
    return root;
  }
  
  // Two-child remove
  if (node1->left_ != NULL && node1->right_ != NULL) {
     
     // Find the IOS
     TreeNode * ios = node1->right_;
     while (ios->left_ != NULL) {
      ios = ios->left_;
     }
     
     node1->val_ = ios->val_;
     node1->right_ = deleteNode(node1->right_, ios->val_);
     // recursive call, just change the value and (don't even need to swap the value), then delete the ios in the right tree of the node
     return root;
  }
}

void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left_);
    std::cout << node->val_ << " ";
    inorderPrint(node->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
