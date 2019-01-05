// Animal.cpp
#include "Animal.h"

#include <string>
#include <iostream>

using namespace std;

Animal::Animal() {
	food_ = "fish";
	type_ = "cat";
}
Animal::Animal(string type, string food) {
	food_ = food;
	type_ = type;
}
string Animal::getType() {
	return type_;
}
string Animal::getFood() {
	return food_;
}
void Animal::setType(string type) {
	type_ = type;
}
void Animal::setFood(string food) {
	food_ = food;
}
string Animal::print() {
	// std::cout << "I am a " << this->getType() << " ." << std::endl;
	string out = "I am a " + this->getType() + " .";
	return out;
}
