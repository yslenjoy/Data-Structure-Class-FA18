#include "Friend.h"

vector<int> addelements(int num, vector<int> arr_) {
	for (int i = 0; i < num; i++) {
    arr_.push_back(-1);
  }
  return arr_;
}

// int find(int x, std::vector<int>& parents) {
//    // your code
// }

int find(int elem, vector<int> arr_) {
  if (arr_[elem] < 0) {
    return elem;
  } else {
    int root = find(arr_[elem], arr_);
    arr_[elem] = root;
    return root;
  }
}

vector<int> setunion(int a, int b, vector<int> arr_) {
  int roota = find(a, arr_);
  int rootb = find(b, arr_);

  int newSize = arr_[roota] + arr_[rootb];
  // Unoin smaller set with larger set (smaller set: less negative)
  if (arr_[roota] < arr_[rootb]) { // roota is the larger set
    arr_[rootb] = roota;
    arr_[roota] = newSize;
  } else { // root b is the larger set
    arr_[roota] = rootb;
    arr_[rootb] = newSize;
  }
  return arr_;
}

int findCircleNum(std::vector<std::vector<int>>& M) {
    // your code
    int num = (int)M[0].size();
    vector<int> arr_;
    arr_ = addelements(num, arr_);

    for (int i = 0; i < num; i++) {
    	for (int j = i+1; j < num; j++) {
    		if (M[i][j] == 1) {
    			arr_ = setunion(i, j, arr_);
    		}
    	}
    }

    int count = 0;
    for (unsigned i = 0; i < arr_.size(); i++) {
    	if (arr_[i] < 0) {
    		count++;
    	}
    }
    return count;
}


