#include <vector>
#include <string>
#include "Hash.h"
// potd 40

using namespace std;

int hashFunction(string s, int M) {
   // Your Code Here
   //hash function to sum up the ASCII characters of the letters of the string
   int sumValue = 0;
   for (int i = 0; i < s.size(); i++) {
   	sumValue += int(s[i]);
   }
   return sumValue % M;
 }

int countCollisions (int M, vector<string> inputs) {
	int collisions = 0;
	// Your Code Here
	std::vector<bool> v;
	for (int i = 0; i < M; i++) {
		v.push_back(0);
	}
	for (int j = 0; j < inputs.size(); j++) {
		int hashValue = hashFunction(inputs[j], M);
		if (v[hashValue] == 0) {
			v[hashValue] = 1;
		} else {
			collisions++;
		}
	}
	return collisions;
}
