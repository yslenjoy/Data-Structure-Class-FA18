#include <vector>
#include "Primes.h"
#include <iostream>

using namespace std;

std::vector<int> *genPrimes(int M) {
    std::vector<int> *v = new std::vector<int>();
    // your code here
    v->push_back(2); // edge case
    for (int i = 2; i < M + 1; i++) {
    	for (int j = 2; j < i; j++) {
    		if (i % j == 0) {
    			break;
    		} else if (i == j + 1) {
    			v->push_back(i);
    			// cout << i << endl;
    		}
    	}
    }
    return v;
}

