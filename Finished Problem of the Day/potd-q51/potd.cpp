#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

string findMaxValue(map<string, int> mymap) {
    int count = 0;
    string curMax;
    for (auto i : mymap) {
        if (i.second > count) {
            count = i.second;
            curMax = i.first;
        }
    }
    return curMax;
}


vector<string> topThree(string filename) {
    string line;
    ifstream infile (filename);
    vector<string> ret;

    map<string, int> mymap;
    map<string, int>::iterator it;

    if (infile.is_open()) {
        while (getline(infile, line)) {
            // do things
            // cout << line << endl;
            it = mymap.find(line);
            if (it == mymap.end()) {
                mymap[line] = 1;
            } else {

                mymap[line] += 1;
            }
        }
    }
    infile.close();

    int count = 3;
    while (count > 0) {
        string tmp = findMaxValue(mymap);
        ret.push_back(tmp);
        mymap.erase(tmp);
        count--;
        // cout << tmp << endl; // 73, 3
    }
    return ret;
}

