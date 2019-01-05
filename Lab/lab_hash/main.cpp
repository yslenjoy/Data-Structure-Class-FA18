#include <iostream>

#include "lphashtable.h"
#include "schashtable.h"
#include "dhhashtable.h"

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
    std::cout << "This main file is for you to write and run your own test cases." << std::endl;
    std::cout << "To run the provided test cases, run `./test`" << std::endl;
    // feel free to insert manual test cases here
    std::vector<std::string> strings;
  	for(int i = 'a'; i <= 'z'; i++) {
  		std::string word = "";
  		word += ((char)i);
  		strings.push_back(word);
  	}
    SCHashTable<string, int> hashTable(16);
  	int val = 0;
  	for(unsigned int i = 0; i < strings.size(); i++) {
  		val++;
  		hashTable.insert(strings[i], val);
  	}
    std::cout << strings.size() << std::endl;
    std::cout << hashTable.tableSize() << std::endl;
    return 0;
}
