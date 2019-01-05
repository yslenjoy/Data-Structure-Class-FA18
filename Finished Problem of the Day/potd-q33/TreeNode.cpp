#include "TreeNode.h"
#include <algorithm>
using namespace std;

// potd 38
int getHeight(TreeNode* subRoot) {
	if (subRoot == NULL) {
		return -1;
	}
	return 1 + max(getHeight(subRoot->left_), getHeight(subRoot->right_));
}

int getb(TreeNode * root) {
  int b = getHeight(root->right_) - getHeight(root->left_);
  return b;
}

void rightRotate(TreeNode* root) {
    // Your code here
	TreeNode* originParent = root->parent_; // might be NULL
    TreeNode* y = root->left_;
    TreeNode* tmp = y->right_; // might be NULL

    // swap y and root's value (it's actually not needed)
    // int tmpValue = root->val_;
    // root->val_ = y->val_;
    // y->val_ = tmpValue;

    if (originParent != NULL) {   
        originParent->left_ = y;
    }
    y->parent_ = originParent;

    y->right_ = root;
    root->parent_ = y;

    root->left_ = tmp;
    if (tmp != NULL) {
        tmp->parent_ = root;
    }
}


void leftRotate(TreeNode* root) {
    // your code here
    TreeNode* originParent = root->parent_;
	TreeNode* y = root->right_;
    TreeNode* tmp = y->left_;

    // swap y and root's value (it's actually not needed)
    // int tmpValue = root->val_;
    // root->val_ = y->val_;
    // y->val_ = tmpValue;

    if (originParent != NULL) { // need to consider this case
        originParent->right_ = y; // root should be the right child, or it will be a complex rotation
    }
    y->parent_ = originParent;

    y->left_ = root;
    root->parent_ = y;

    root->right_ = tmp;
    if (tmp != NULL) { // need to consider this case
        tmp->parent_ = root;
    }
}



void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

