#include "potd.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	// test your code here!
	std::vector<string> v = topThree("in1.txt");
	for (auto i : v) {
		cout << i << endl;
	}
	return 0;
}
