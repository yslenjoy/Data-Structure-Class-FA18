#include "Hash.h"
#include <string>
#include <algorithm> 


unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	//Your code here
	for (unsigned i = 0; i < str.size(); i++) {
		b_hash *= 33 ;
		b_hash += int(str[i]);
	}
	return b_hash % M;
}

std::string reverse(std::string str)
{
    // std::string output = "";
	//Your code here
	std::reverse(str.begin(), str.end());

	return str;
}
