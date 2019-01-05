#include "TreeNode.h"

TreeNode::RotationType balanceTree(TreeNode*& subroot) {
	// Your code here
	
	// NULL case: not necessarily
	// subroot is NULL or subtree is leaf node: don't need to do the rotation
	// if no rotation case exists, the enum will give related return type
	// if (subroot == NULL) {
	// 	return TreeNode::NULL;
	// }
	// if (subroot->left_ == NULL && subroot->right_ == NULL) {
	// 	return TreeNode::NULL;
	// }

	TreeNode* l = subroot->left_;
	TreeNode* r = subroot->right_;
	int b = getHeight(subroot->right_) - getHeight(subroot->left_);

	if (b >= 2) {
		int bb = getHeight(r->right_) - getHeight(r->left_);
		if (bb == -1) {
			return TreeNode::rightLeft;
		}
		if (bb == 1) {
			return TreeNode::left;
		} else {
			balanceTree(subroot->right_); // may not be the lowest unblanced node
			// althought the function is ptr by reference, when passing by ptr, the function will take it as reference, no special action to make the ptr as reference
		}
	}
	if (b <= -2) {
		int bb = getHeight(l->right_) - getHeight(l->left_);
		if (bb == -1) {
			return TreeNode::right;
		}
		if (bb == 1) {
			return TreeNode::leftRight;
		} else {
			balanceTree(subroot->left_);
		}
	}
  return TreeNode::right;
}
