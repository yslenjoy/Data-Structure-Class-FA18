// your code here
#include "q5.h"
#include "Food.h"
#include <iostream>

using namespace std;

int main() {
	Food f;

	f.set_quantity(5);

	string name = f.get_name();
	int quantity = f.get_quantity();
	string tmp = "s.";
	if (quantity <= 1) { // sigular situation
		tmp = ".";
	}
	cout << "You have " << quantity << " " << name << tmp << endl;

	// increase one
	tmp = "s.";
	Food* fptr = & f;
	Food newFood = increase_quantity(fptr);
	cout << "You have " << newFood.get_quantity() << " " << name << tmp << endl;
	return 0;
}