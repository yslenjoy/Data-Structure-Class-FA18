// your code here
#include "q5.h"
#include <iostream>

Food increase_quantity(Food * someFood) {
	int q = someFood->get_quantity();
	someFood->set_quantity(q+1);
	return *someFood;
}