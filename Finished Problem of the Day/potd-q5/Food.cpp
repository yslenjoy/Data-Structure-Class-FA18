// Your code here
#include "Food.h"
#include <string>

using namespace std;

Food::Food() {
	quantity_ = 0;
	name_ = "apple";
}

string Food::get_name() {
	return name_;
}
int Food::get_quantity() {
	return quantity_;
}
void Food::set_name(string newName) {
	name_ = newName;
}
void Food::set_quantity(int newQuantity) {
	quantity_ = newQuantity;
}
