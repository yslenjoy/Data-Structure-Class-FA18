#include "TreeNode.h"
#define NOMINMAX
#include <algorithm>

using namespace std;

int getHeight(TreeNode* subRoot) {
	if (subRoot == NULL) {
		return -1;
	}
	return 1 + max(getHeight(subRoot->left_), getHeight(subRoot->right_));
}

bool isHeightBalanced(TreeNode* root) {
  // your code here
  if (root == NULL) {return true;}
  // in the case, I use recursion method,
  // however, recursion is not that elegant, comparing the height of left and right should be enough, since getHeight() function takes the max of left and right child.
  // height difference greater than 1 and both left and right are balanced are equivalant in this case.
  if (root->right_ == NULL && root->left_ == NULL) {
  	return true;
  }
  if (root->right_ == NULL && root->left_ != NULL) {
  	int h1 = getHeight(root->left_);
  	if (h1 < 1) {
  		return true;
  	} else {
  		return false;
  	}
  }
  if (root->right_ != NULL && root->left_ == NULL) {
  	int h1 = getHeight(root->right_);
  	if (h1 < 1) {
  		return true;
  	} else {
  		return false;
  	}
  }

  bool b1 = isHeightBalanced(root->left_);
  bool b2 = isHeightBalanced(root->right_);
  if (b1 && b2) {
  	return true;
  } else {
  	return false;
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

