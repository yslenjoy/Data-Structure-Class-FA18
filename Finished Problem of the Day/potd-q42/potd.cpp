#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

unordered_map<string, int> common_elems(unordered_map<string, int> &mapA,
                                        unordered_map<string, int> &mapB) {

    // your code here
	
	unordered_map<string, int> result;
	result = unordered_map<string, int> ();
	std::vector<string> v1;
	std::vector<string> v2;
	// cout << mapA.begin()->first << endl;
	for (auto itrA = mapA.begin(); itrA != mapA.end(); ++itrA) {
		auto same1 = mapB.find(itrA->first);
		if (same1 != mapB.end()) {
			result[itrA->first] = same1->second + itrA->second;
			v1.push_back(itrA->first);
		}
	}
	for (auto itrB = mapB.begin(); itrB != mapA.end(); ++itrB) {
		auto same2 = mapA.find(itrB->first);
		if (same2 != mapA.end()) {
			// cout << itrB->first << endl;
			v2.push_back(itrB->first);
		}
	}
	for (auto &it : v1) {
		mapA.erase(it);
	}
	for (auto &it : v2) {
		mapB.erase(it);
	}
    return result;
    // return mapB;
} 