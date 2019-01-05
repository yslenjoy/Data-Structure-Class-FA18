#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Hash.h"

using namespace std;

unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	for (int i = 0; i < (int) str.length(); ++i)
	{
		b_hash = b_hash * 33 + str[i];
	}
	return b_hash % M;
}

float hash_goodness(std::string str, int M)
{
    // std::vector<int>* array = new std::vector<int>(M);	// Hint: This comes in handy
    std::vector<int> v(M);
    for (unsigned i = 0; i < v.size(); i++) {
    	v[i] = 0;
    }
	int permutation_count = 0;	
	float goodness = 0;
	int collisions = 0;
	do {
		if (permutation_count == M) break;
		// Code for computing the hash and updating the array
		int result = (int)bernstein(str, M);
		if (v[result] == 0) {
			v[result] = 1;
		} else {
			collisions++;
		}
		// cout << *array << endl;
		permutation_count++;
	} while(std::next_permutation(str.begin(), str.end()));
	
	//Code for determining goodness
	goodness = (float)collisions / (float)M;
	return goodness;
}

