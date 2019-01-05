#include "List.h"
#include "cs225/catch/catch.hpp"
#include "tests/tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;
using namespace std;


int main() {
	// PNG in;        in.readFromFile("tests/alma.png");
	// PNG expected;  expected.readFromFile("tests/expected-reserve.png");

	// List<HSLAPixel> list = imageToList(in);
	// list.reverse();
	// PNG out = listToImage(list, in.width(), in.height());
	// out.writeToFile("actual-reserve.png");
	List<int> list;
  for (int i = 0; i < 5; i++) { list.insertBack(i); }
  // list.insertFront(99);
  list.insertFront(78);
  list.insertBack(32);
  // list.insertBack(77);
  // list.insertBack(77);
  list.insertBack(77);
	list.insertFront(8);
  List<int>::ListIterator it;
	list.print(std::cout);
	cout << ""<< std::endl;
	// list.waterfall();
	// List<int> listRight1 = list.split(4); // 2 3 4 32 77
	list.sort();
	cout << ""<< std::endl;

  return 0;
}
