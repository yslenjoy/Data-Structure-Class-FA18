#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int TreeNode::getHeight() {
  if (left_ == NULL && right_ == NULL) {
  	return 0;
  }
  if (left_ ==  NULL) {
  	return (1 + right_->getHeight());
  }
  if (right_ == NULL) {
  	return (1 + left_->getHeight());
  }
  int leftH = left_->getHeight();
  int rightH = right_->getHeight();
  if (leftH > rightH) {
  	return 1+leftH;
  } else {
  	return 1+rightH;
  }
}
