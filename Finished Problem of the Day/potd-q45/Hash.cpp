#include <vector>
#include <iostream>
#include "Hash.h"

void doubleHashInput(std::vector<int> &v, int elem){
	//your code here
	int size = (int)v.size();
	int idx = firstHash(elem, size);
	int h = idx;

	// for (int i = 0; i < size; i++) {
	// 	v[i] = -1; // empty state: -1
	// }

  int i = 0;
  while (v[idx] != -1) {
  	i++;
  	int step = secondHash(elem);
  	idx = (h + step * i) % size;
  }
  v[idx] = elem;
}

//make a hash function called firstHash
int firstHash(int elem, int length) {
	return elem * 4 % length;
}

//make a second function called secondHash
int secondHash(int elem) {
	return 3 - elem % 3;
}
