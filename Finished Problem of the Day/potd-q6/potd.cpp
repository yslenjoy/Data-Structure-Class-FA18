// your code here!
#include "potd.h"
#include <iostream>
#include <math.h> //pow

using namespace std;

namespace potd {
	int *raise(int *arr) {
		int length = 0;
		while (arr[length] >= 0) {
			length++;
		}
		length++;
		// cout << length << endl;
		int * array = new int[length];
		for (int x = 0; x < length; x++) {
			array[x] = arr[x];
		}
		if (length == 2) {
			return array;
		}
		for (int x = 0; x < length - 2; x++) {
			array[x] = pow(array[x], array[x+1]);
		}
		// delete[] array;
		// delete[]: just free the memory address, 
		// but the data are still on that address untill t
		// hey are used by others.
		return array;
	}
}