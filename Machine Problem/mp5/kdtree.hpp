/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (curDim < 0 || curDim > Dim) {
       return false;
     }
     if (first[curDim] < second[curDim]) {
       return true;
     } else if (first[curDim] > second[curDim]) {
       return false;
     } else {
       return (first < second);
     }
    // return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double cur_dist = 0.0;
     double pot_dist = 0.0;
     for (int i = 0; i < Dim; i++) {
       cur_dist += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
       pot_dist += (target[i] - potential[i]) * (target[i] - potential[i]);
     }
     if (cur_dist > pot_dist) {
       return true;
     } else if (cur_dist < pot_dist) {
       return false;
     } else {
       return (potential < currentBest);
     }
     // return false;
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dimension)
{
  Point<Dim> pivotValue = this->points[pivotIndex];
  // swap pivotValue to vector end, temporarily
  swap(this->points[pivotIndex], this->points[right]);
  int storeIndex = left;
  for (int i = left; i < right; i++) {
    //compare with value of at pivotIndex, keep swapping larger ones to right
    if (smallerDimVal(this->points[i], pivotValue, dimension)) {
      swap(this->points[storeIndex], this->points[i]);
      storeIndex++;
    }
  }
  swap(this->points[right], this->points[storeIndex]);
  return storeIndex;
}

template <int Dim>
void KDTree<Dim>::select(int left, int right, int k, int dimension)
{
  if (left == right) {
    return;
  }
  int pivotIndex = (left + right) / 2;
  pivotIndex = partition(left, right, pivotIndex, dimension);

  // if it's already at median position, we are done
  // else, search for it in left or right parts
  if (k == pivotIndex) {
    return;
  } else if (k < pivotIndex) {
    select(left, pivotIndex - 1, k, dimension);
  } else {
    select(pivotIndex + 1, right, k, dimension);
  }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::quickSort(int low, int high, int dimension) {
  // Original implementation a void function, node is passed by ptr by reference,
  // some weird error occured in this way, so just change the return type into
  // KDTreeNode* (typename is needed here)
  if (low > high) { // rather than low >= high (leaf node case)
    return NULL;
  }
  int mid = (low + high) / 2;
  select(low, high, mid, dimension); // ensure mid is the mid point
  KDTreeNode* subroot = new KDTreeNode(this->points[mid]);
  subroot->left = quickSort(low, mid - 1, (dimension + 1) % Dim);
  subroot->right = quickSort(mid + 1, high, (dimension + 1) % Dim);
  return subroot;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    this->points = newPoints;
    if (points.size() == 1) {
      return;
    }
    int left = 0;
    int right = points.size() - 1;
    root = quickSort(left, right, 0);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(const KDTree<Dim>& other)
{
  this->points = other->points;
  if (points.size() == 1) {
    return;
  }
  int left = 0;
  int right = points.size() - 1;
  root = quickSort(left, right, 0);
  return root;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  root = copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
    clear(rhs.root);
    root = copy(rhs);
  }
  return *this;
}

template <int Dim>
void KDTree<Dim>::clean(KDTreeNode* subroot)
{
  if (subroot == NULL) {
    return;
  }
  clean(subroot->left);
  clean(subroot->right);
  delete subroot;
  subroot = NULL;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clean(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  /**
    * @todo Implement this function!
   */
  if (points.empty()) {
    return Point<Dim>();
  }
  return NNHelper(query, 0, points.size() - 1, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::NNHelper(const Point<Dim>& query, int low, int high, int dimension) const
{
  Point<Dim> curBest;
  int mid = (low + high) / 2;
  if (low > high) { // or low >= high doesn't matter here since there is no node created (not leaf node case)
    return points[mid];
  }
  int nextDim = (dimension + 1) % Dim;
  if (smallerDimVal(query, points[mid], dimension)) {
    // go left
    curBest = NNHelper(query, low, mid - 1, nextDim);
  } else {
    // go right
    curBest = NNHelper(query, mid + 1, high, nextDim);
  }

  // check leaf is actually better than parent node
  if (shouldReplace(query, curBest, points[mid])) {
    curBest = points[mid];
  }

  // curBest distance
  double curBest_d = 0;
  for (int i = 0; i < Dim; i++) {
    curBest_d += (query[i] - curBest[i]) * (query[i] - curBest[i]);
  }

  // distance to the parent
  double mid_d = (query[dimension] - points[mid][dimension]) * (query[dimension] - points[mid][dimension]); // not nextDim (should be current dimension of the function call)

  // check whether we should go another side of the tree or not
  if (mid_d <= curBest_d) {
    Point<Dim> anotherBest;
    if (smallerDimVal(query, points[mid], dimension)) {
      // go to another side, in this case, it should be go right
      anotherBest = NNHelper(query, mid + 1, high, nextDim);
    } else {
      // go left
      anotherBest = NNHelper(query, low, mid - 1, nextDim);
    }
    if (shouldReplace(query, curBest, anotherBest)) {
      curBest = anotherBest;
    }
  }

  return curBest;
}
