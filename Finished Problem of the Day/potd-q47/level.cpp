#include "MinHeap.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

vector<int> lastLevel(MinHeap & heap)
{
    // Your code here
    int size = (int)heap.elements.size();
    std::vector<int> result;
    // cout << size << endl; // including the -inf one
    int h = log2(size - 1); // interger division: floor stuff
    int lo = pow(2, h);
    for (int i = lo; i < size; i++) {
    	result.push_back(heap.elements[i]);
    }
    return result;

}

