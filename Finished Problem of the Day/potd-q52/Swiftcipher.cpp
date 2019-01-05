#include "Swiftcipher.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

/* Swift Cipher: Frequency of words in a file corresponds to its location in the decrypted sentence */
string decipherer(string filename) {
	string line;
	ifstream infile (filename);
	string result = "";

	map<string, int> mymap;

	if (infile.is_open()) {
		while (getline(infile, line)) {
			auto it = mymap.find(line);
			if (it == mymap.end()) {
				mymap[line] = 1;
			} else {
				mymap[line] += 1;
			}
		}
	}
	infile.close();

	int size = (int)mymap.size();
	for (int i = 1; i <= size; i++) {
		for (auto it : mymap) {
			if (it.second == i) {
				result += it.first;
				if (i != size) {
					result += " ";
				}
				break;
			}
		}
	}
	return result;
}
