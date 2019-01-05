#include <vector>
#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    arr_.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (arr_[elem] < 0) {
    return elem;
  } else {
    int root = find(arr_[elem]);
    arr_[elem] = root;
    return root;
  }
}

void DisjointSets::setunion(int a, int b) {
  int roota = find(a);
  int rootb = find(b);

  int newSize = arr_[roota] + arr_[rootb];
  // Unoin smaller set with larger set (smaller set: less negative)
  if (arr_[roota] < arr_[rootb]) { // roota is the larger set
    arr_[rootb] = roota;
    arr_[roota] = newSize;
  } else { // root b is the larger set
    arr_[roota] = rootb;
    arr_[rootb] = newSize;
  }
}

int DisjointSets::size(int elem) {
  int size = find(elem);
  return -(arr_[size]);
}
