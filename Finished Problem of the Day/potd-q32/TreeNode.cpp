#include "TreeNode.h"
#include <algorithm>
#include <iostream>

using namespace std;

int getHeight(TreeNode* subRoot) {
	if (subRoot == NULL) {
		return -1;
	}
	return 1 + max(getHeight(subRoot->left_), getHeight(subRoot->right_));
}

bool isHeightBalanced(TreeNode* root) {
  // your code here
	if (root == NULL){
		return true;
	}
	int l = getHeight(root->left_);
	int r = getHeight(root->right_);
	if (l-r > 1 || r-l > 1){
		return false;
	}
  	return true;
}

bool isAVL(TreeNode* subRoot) {
	if (subRoot == NULL) {
		return true;
	}
	if (isHeightBalanced(subRoot)) {
		return (isHeightBalanced(subRoot->left_) && isHeightBalanced(subRoot->right_));
	}
	return false;
}


TreeNode* findLastUnbalanced(TreeNode* root) {
  // your code here
  if (root == NULL) {return NULL;}
  if (!isAVL(root)) {
  	if (!isAVL(root->left_)) {
  		return findLastUnbalanced(root->left_);
  	} else if (!isAVL(root->right_)) {
  		return findLastUnbalanced(root->right_);
  	} else {
  		return root;
  	}
  }
  return NULL;

}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}

