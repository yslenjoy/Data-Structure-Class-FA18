#include <iostream>
#include "potd.cpp"

using namespace std;

int main() {
    // nordered_map<string, int> mapA({
    //                                 {"common", 13}, 
    //                                 {"unique_a", 13}
    //                                 });
    // unordered_map<string, int> mapB({
    //                                 {"common", 17}, 
    //                                 {"unique_b", 17}
    //                                 });u

    unordered_map<string, int> mapA({
                                    {"common", 13}, 
                                    {"hello", -1}, 
                                    {"things", 6},
                                    {"A", 1},
                                    {"unique_a", 13}
                                    });
    unordered_map<string, int> mapB({
                                    {"common", 17}, 
                                    {"hello", 5}, 
                                    {"things", 20},
                                    {"b", 1},
                                    {"unique_b", 17}
                                    });

    unordered_map<string, int> common = common_elems(mapA, mapB);

    // check your outputs here
    cout << "Intersection:" <<endl;
    cout << "empty?: " << common.empty() << endl;
    for (auto it : common) {
        cout << it.first << ", " << it.second << endl;
    }
    cout << "" <<endl;

    cout << "mapA:" <<endl;
    for (auto it : mapA) {
        cout << it.first << ", " << it.second << endl;
    }
    cout << "" <<endl;

    cout << "mapB:" <<endl;
    for (auto it : mapB) {
        cout << it.first << ", " << it.second << endl;
    }
    cout << "" <<endl;
}
