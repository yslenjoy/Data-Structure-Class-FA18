#include <vector>
#include "BTreeNode.h"

using namespace std;

std::vector<int> traverse(BTreeNode* root) {
    // your code here
    std::vector<int> v;
    if (root->elements_.empty()) {
    	return v;
    }
    for (int i = 0; i < root->elements_.size(); i++) {
    	if (root->is_leaf_) {
    		v.push_back(root->elements_[i]);
    	} else {
    		// left most child
    		std::vector<int> tmp1 = traverse(root->children_[i]);
    		v.insert(v.end(), tmp1.begin(), tmp1.end());

    		v.push_back(root->elements_[i]);

    		if (i == root->elements_.size()-1) { // right most
    			std::vector<int> tmp2 = traverse(root->children_[i+1]);
    			v.insert(v.end(), tmp2.begin(), tmp2.end());
    		}
    	}
    }
    return v;
}
