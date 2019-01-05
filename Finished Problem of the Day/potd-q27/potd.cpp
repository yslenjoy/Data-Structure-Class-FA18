// Your code here
#include "potd.h"
#include <vector>

string getFortune(const string &s) {
	std::vector<string> v;
	v.push_back("Ptr by reference, prt array.....");
	v.push_back("Absolutely yes");
	v.push_back("Run GDB yourself to find it!!!!");
	v.push_back("Think about Savi, definitely no!");
	v.push_back("I don't know");
	int mod = s.length() % 5;
	return v[mod];
}